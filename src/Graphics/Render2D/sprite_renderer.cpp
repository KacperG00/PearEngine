#include "sprite_renderer.h"

#include <iostream>

namespace pear { namespace graphics {
	
	unsigned int SpriteRenderer::WAIT = 0;
	
	SpriteRenderer::SpriteRenderer()
		: m_IBO( 0 )
	{
		initShaders();
		initIBO();
	}
	
	SpriteRenderer::~SpriteRenderer()
	{
		for( int i = m_Sprites.size() - 1; i >= 0; i-- )
		{
			delete m_Sprites[i];
			m_Sprites[i] = NULL;
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
					vertexData[i].setColor( ((Sprite*)renderable)->col.r, ((Sprite*)renderable)->col.g, ((Sprite*)renderable)->col.b, ((Sprite*)renderable)->col.a );
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
		}
		
		vertexData[0].setUV( 0.0f, 1.0f );
		vertexData[1].setUV( 1.0f, 1.0f );
		vertexData[2].setUV( 0.0f, 0.0f );
		vertexData[3].setUV( 1.0f, 0.0f );
		
		vertexData[0].setPosition( 0.0f - (renderable->w / 2.0f), 0.0f + (renderable->h / 2.0f), renderable->z );
		vertexData[1].setPosition( 0.0f + (renderable->w / 2.0f), 0.0f + (renderable->h / 2.0f), renderable->z );
		vertexData[2].setPosition( 0.0f - (renderable->w / 2.0f), 0.0f - (renderable->h / 2.0f), renderable->z );
		vertexData[3].setPosition( 0.0f + (renderable->w / 2.0f), 0.0f - (renderable->h / 2.0f), renderable->z );
		
		renderable->transMat = glm::translate( renderable->transMat, glm::vec3( renderable->x + renderable->w / 2.0f, renderable->y - renderable->h / 2.0f, 0.0f ) );
		
		if( renderable->vbo == 0 )
			glGenBuffers( 1, &renderable->vbo );
		
		glBindBuffer( GL_ARRAY_BUFFER, renderable->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		
		m_Sprites.push_back( renderable );
	}
	
	void SpriteRenderer::flush()
	{
		for( int i = 0; i < m_Sprites.size(); i++ )
		{
			m_Shader.use();
			
			if( m_Sprites[i]->texture != nullptr )
			{
				m_Shader.setUniform1i( "diffuse_texture", GL_TEXTURE0 );
				glActiveTexture( GL_TEXTURE0 );
				glBindTexture( GL_TEXTURE_2D, m_Sprites[i]->texture->textureID );
				
				if( m_Sprites[i]->renderableType == Renderable2D::RenderableType::SPRITESHEET
					&& ((SpriteSheet*)m_Sprites[i])->ready() )
				{
					if( WAIT % 10 == 0 )
						((SpriteSheet*)m_Sprites[i])->nextFrame();
					glm::vec4* texMod = ((SpriteSheet*)m_Sprites[i])->getCurrFrame();
					m_Shader.setUniform4f( "texCoordsModifier", *texMod );
				}
				else
				{
					m_Shader.setUniform4f( "texCoordsModifier", glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) );
				}
				
			}
			
			glm::mat4 transformationMatrix = m_Sprites[i]->transMat * m_Sprites[i]->rotationMat * m_Sprites[i]->scaleMat;
			m_Shader.setUniformMat4( "transMat", transformationMatrix );
			
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
			glBindBuffer( GL_ARRAY_BUFFER, m_Sprites[i]->vbo );
			
			glVertexAttribPointer( m_AttributeNum + 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, position ) );
			glVertexAttribPointer( m_AttributeNum + 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, color ) );
			glVertexAttribPointer( m_AttributeNum + 2, 1, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, tid ) );
			glVertexAttribPointer( m_AttributeNum + 3, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, uv ) );
			
			glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
			
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
			
			m_Shader.unuse();
		}
	}
	
	void SpriteRenderer::transformMatrix( unsigned int sprite_slot, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale, float angle )
	{
		m_Sprites[sprite_slot]->transMat = glm::translate( m_Sprites[sprite_slot]->transMat, translation );
		m_Sprites[sprite_slot]->rotationMat = glm::rotate( m_Sprites[sprite_slot]->rotationMat, glm::radians(angle), rotation );
		m_Sprites[sprite_slot]->scaleMat = glm::scale( m_Sprites[sprite_slot]->scaleMat, scale );
	}
	
	void SpriteRenderer::transformMatrix( unsigned int sprite_slot, const glm::vec3& transformation, const unsigned int transformation_type, float angle )
	{
		switch( transformation_type )
		{
			case PEAR_TRANSFORM_TRANSLATE:
				m_Sprites[sprite_slot]->transMat = glm::translate( m_Sprites[sprite_slot]->transMat, transformation );
				break;
			case PEAR_TRANSFORM_ROTATE:
				m_Sprites[sprite_slot]->rotationMat = glm::rotate( m_Sprites[sprite_slot]->rotationMat, glm::radians(angle), transformation );
				break;
			case PEAR_TRANSFORM_SCALE:
				m_Sprites[sprite_slot]->scaleMat = glm::scale( m_Sprites[sprite_slot]->scaleMat, transformation );
				break;
		}
	}
	
	void SpriteRenderer::initShaders()
	{
		m_AttributeNum = Shader::numAttributes;
		
		m_Shader.compileShaders( "standard_sprite_shader" );
		m_Shader.addAttribute( "vsPosition" );
		m_Shader.addAttribute( "vsColor" );
		m_Shader.addAttribute( "vsTID" );
		m_Shader.addAttribute( "vsUV" );
		m_Shader.linkShaders();
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
