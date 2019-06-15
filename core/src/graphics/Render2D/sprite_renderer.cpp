#include "PEngine/graphics/sprite_renderer.h"

#include "PEngine/app/resource_manager.h"

#include "PEngine/graphics/group.h"
#include "PEngine/graphics/label.h"

#include "PEngine/utilities/load_text_file.h"

namespace pear { namespace graphics {
	
	SpriteRenderer::SpriteRenderer()
		: m_IBO( 0 )
	{
		m_Shader = nullptr;
		initIBO();
	}
	
	SpriteRenderer::~SpriteRenderer()
	{
		for( int i = m_Sprites.size() - 1; i >= 0; i-- )
		{
			m_Sprites[i]->renderer = nullptr;
			m_Sprites.pop_back();
		}
		
		if( m_IBO != 0 )
			glDeleteBuffers( 1, &m_IBO );
	}
	
	void SpriteRenderer::submit( Renderable2D* renderable )
	{
		Vertex vertexData[4];
		
		switch( renderable->renderableType )
		{
			case Renderable2D::RenderableType::SPRITE:
			{
				for( int i = 0; i < 4; i++ )
				{
					vertexData[i].setColor( ((Sprite*)renderable)->col.r,
											((Sprite*)renderable)->col.g,
											((Sprite*)renderable)->col.b,
											((Sprite*)renderable)->col.a );
					
					vertexData[i].tid = ((Sprite*)renderable)->textureID;
				}
			} break;
			case Renderable2D::RenderableType::SPRITESHEET:
			{
				for( int i = 0; i < 4; i++ )
				{
					vertexData[i].setColor( 255, 0, 255, 255 );
					vertexData[i].tid = renderable->texture->textureID;
				}
			} break;
			case Renderable2D::RenderableType::GROUP:
			{
				for( int i = 0; i < ((Group*)renderable)->renderables.size(); ++i )
				{
					this->submit( ((Group*)renderable)->renderables[i] );
				}
			} break;
		}
		
		if( renderable->renderableType != Renderable2D::RenderableType::GROUP )
		{
			vertexData[0].setUV( renderable->uv.x, renderable->uv.w );
			vertexData[1].setUV( renderable->uv.z, renderable->uv.w );
			vertexData[2].setUV( renderable->uv.x, renderable->uv.y );
			vertexData[3].setUV( renderable->uv.z, renderable->uv.y );
			
			vertexData[0].setPosition( 0.0f - (renderable->w / 2.0f), 0.0f + (renderable->h / 2.0f), renderable->z );
			vertexData[1].setPosition( 0.0f + (renderable->w / 2.0f), 0.0f + (renderable->h / 2.0f), renderable->z );
			vertexData[2].setPosition( 0.0f - (renderable->w / 2.0f), 0.0f - (renderable->h / 2.0f), renderable->z );
			vertexData[3].setPosition( 0.0f + (renderable->w / 2.0f), 0.0f - (renderable->h / 2.0f), renderable->z );
			
			renderable->transform( 	PEAR_TRANSFORM_TRANSLATE,
									glm::vec3( 	renderable->x + renderable->w / 2.0f,
												renderable->y - renderable->h / 2.0f,
												0.0f ) );
			
			if( renderable->vbo == 0 )
				glGenBuffers( 1, &renderable->vbo );
			
			glBindBuffer( GL_ARRAY_BUFFER, renderable->vbo );
			glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			
			m_Sprites.push_back( renderable );
		}
		
		renderable->renderer = this;
	}
	
	void SpriteRenderer::erase( Renderable2D* renderable )
	{
		for( int i = 0; i < m_Sprites.size(); ++i )
		{
			if( m_Sprites[i]->id == renderable->id )
			{
				m_Sprites[i]->renderer = nullptr;
				m_Sprites.erase( m_Sprites.begin() + i );
			}
		}
	}
	
	void SpriteRenderer::flush()
	{
		if(m_Shader)
		{
			for( int i = 0; i < m_Sprites.size(); ++i )
			{
				m_Shader->use();
				
				if( m_Sprites[i]->texture != nullptr )
				{
					m_Shader->setUniform1i( "diffuse_texture", GL_TEXTURE0 );
					glActiveTexture( GL_TEXTURE0 );
					glBindTexture( GL_TEXTURE_2D, m_Sprites[i]->texture->textureID );
					
					if( m_Sprites[i]->renderableType == Renderable2D::RenderableType::SPRITESHEET
						&& ((SpriteSheet*)m_Sprites[i])->ready() )
					{
						((SpriteSheet*)m_Sprites[i])->nextFrame();
						glm::vec4* texMod = ((SpriteSheet*)m_Sprites[i])->getCurrFrame();
						m_Shader->setUniform4f( "texCoordsModifier", *texMod );
					}
					else
					{
						m_Shader->setUniform4f( "texCoordsModifier", glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) );
					}
				}
				
				glm::mat4 final_matrix = m_Sprites[i]->globalMat * m_Sprites[i]->localMat;
				m_Shader->setUniformMat4( "transMat", final_matrix );
				
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
				glBindBuffer( GL_ARRAY_BUFFER, m_Sprites[i]->vbo );
				
				glVertexAttribPointer( m_Shader->m_AttributeNum + 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, position ) );
				glVertexAttribPointer( m_Shader->m_AttributeNum + 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, color ) );
				glVertexAttribPointer( m_Shader->m_AttributeNum + 2, 1, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, tid ) );
				glVertexAttribPointer( m_Shader->m_AttributeNum + 3, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, uv ) );
				
				glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
				
				glBindBuffer( GL_ARRAY_BUFFER, 0 );
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
				
				m_Shader->unuse();
			}
		}
	}
	
	void SpriteRenderer::bindShader(const char* shaderName)
	{
		m_Shader = ResourceManager::getShader( shaderName );
	}
	
	void SpriteRenderer::initIBO()
	{
		unsigned int vertices[] =
		{
			0, 1, 2,
			2, 1, 3,
		};
		
		glGenBuffers( 1, &m_IBO );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
	
} }
