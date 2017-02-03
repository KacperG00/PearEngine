#include "static_sprite_renderer.h"

#include "../../resource_manager.h"

namespace pear { namespace graphics {
	
	StaticSpriteRenderer::StaticSpriteRenderer()
		: m_VBO( 0 ), m_IBO( 0 ),
		everySpriteIsDrawn(false), areSpritesWithoutTexturesDrawn(false)
	{
		setUpVBO();
		initShaders();
		clearTextureArray();
	}
	
	StaticSpriteRenderer::~StaticSpriteRenderer()
	{
		if( m_VBO )
			glDeleteBuffers( 1, &m_VBO );
		if( m_IBO )
			glDeleteBuffers( 1, &m_IBO );
			
		for( int i = m_Sprites.size() - 1; i >= 0; i-- )
		{
			delete m_Sprites[i];
			m_Sprites[i] = NULL;
			m_Sprites.pop_back();
		}
		for( int i = 0; i < m_RenderedSprites.size(); i++ )
			m_RenderedSprites.pop_back();
	}
	
	void StaticSpriteRenderer::submit(Renderable2D* sprite)
	{
		if( sprite->renderableType == Renderable2D::RenderableType::SPRITE )
		{
			m_Sprites.push_back( (Sprite*)sprite );
			sortSpritesByTextureID();
		}
	}
	
	void StaticSpriteRenderer::flush()
	{
		areSpritesWithoutTexturesDrawn = false;
		everySpriteIsDrawn = false;
		m_GreatestTextureID = 0;
		
		while(!everySpriteIsDrawn)
		{
			loadSpritesToRender();
			
			m_Shader.use();
			
			bindTextures();
			
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
			glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
			glDrawElements( GL_TRIANGLES, m_RenderedSprites.size() * 6, GL_UNSIGNED_INT, 0 );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
			
			m_Shader.unuse();
		}
	}
	
	void StaticSpriteRenderer::sortSpritesByTextureID()
	{
		if( m_Sprites.size() > 1 )
		{
			for( unsigned int i = 0; i < m_Sprites.size(); i++ )
			{
				if( !m_Sprites[i]->sorted )
				{
					for( unsigned int j = i; j > 0; j-- )
					{
						if( m_Sprites[j]->textureID < m_Sprites[j-1]->textureID )
							swapSprites( j, j-1 );
						else
						{
							m_Sprites[j]->sorted = true;
							break;
						}
					}
				}
			}
		}
		if( m_Sprites.size() > 0 )
			m_Sprites[0]->sorted = true;
	}
	
	void StaticSpriteRenderer::initShaders()
	{
		m_Shader.compileShaders( "static_sprite_shader32" );
		m_Shader.addAttribute( "vsPosition" );
		m_Shader.addAttribute( "vsColor" );
		m_Shader.addAttribute( "vsTextureID" );
		m_Shader.addAttribute( "vsTextureCoords" );
		m_Shader.linkShaders();
	}
	
	void StaticSpriteRenderer::setUpVBO()
	{
		glGenBuffers( 1, &m_VBO );
		glGenBuffers( 1, &m_IBO );
		
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferData( GL_ARRAY_BUFFER, MAX_VERTICES * sizeof( Vertex ), NULL, GL_STATIC_DRAW );
		glVertexAttribPointer( Shader::numAttributes + 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position) );
		glVertexAttribPointer( Shader::numAttributes + 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color) );
		glVertexAttribPointer( Shader::numAttributes + 2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tid) );
		glVertexAttribPointer( Shader::numAttributes + 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv) );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		
		unsigned int indices[MAX_ELEMENTS];
		
		unsigned int x = 0;
		for( unsigned long int i = 0; i < MAX_ELEMENTS; i += 6 )
		{
			indices[ i ] = x;
			indices[i+1] = x + 1;
			indices[i+2] = x + 2;
			indices[i+3] = x + 2;
			indices[i+4] = x + 1;
			indices[i+5] = x + 3;
			
			x += 4;
		}
		
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
	
	void StaticSpriteRenderer::bindTextures()
	{
		GLint textures[TEXTURE_ARRAY_SIZE32];
		for( int i = 0; i < TEXTURE_ARRAY_SIZE32; i++ )
		{
			glActiveTexture( GL_TEXTURE0 + i );
			textures[i] = i;
			glBindTexture( GL_TEXTURE_2D, m_TextureArray[i] );
		}
		
		glUniform1iv(m_Shader.getUniformLocation("textures"), TEXTURE_ARRAY_SIZE32, textures);
		glUniform1uiv(m_Shader.getUniformLocation("arr_TextureID"), TEXTURE_ARRAY_SIZE32, m_TextureArray);
	}
	
	void StaticSpriteRenderer::loadSpritesToRender()
	{
		loadTextures();
		loadPartitionOfSprites();
		sendDataToGPU();
	}
	
	void StaticSpriteRenderer::loadTextures()
	{
		unsigned int countoftextures = 0;
		m_GreatestTextureID = m_TextureArray[TEXTURE_ARRAY_SIZE32 - 1];
		clearTextureArray();
		
		int i = 0;
		while( countoftextures < TEXTURE_ARRAY_SIZE32 && i < m_Sprites.size() )
		{
			if( m_Sprites[i]->textureID > m_GreatestTextureID )
			{
				m_GreatestTextureID = m_Sprites[i]->textureID;
				m_TextureArray[countoftextures] = m_Sprites[i]->textureID;
				countoftextures++;
			}
			
			i++;
		}
	}
	
	void StaticSpriteRenderer::loadPartitionOfSprites()
	{
		unsigned int firstLowestTextureID = 0;
		for( int i = 0; i < m_Sprites.size(); i++ )
		{
			if( m_Sprites[i]->textureID == m_TextureArray[0] )
			{
				firstLowestTextureID = i;
				break;
			}
			if( !areSpritesWithoutTexturesDrawn )
			{
				firstLowestTextureID = 0;
				areSpritesWithoutTexturesDrawn = true;
				break;
			}
		}
		
		unsigned int lastHeighestTextureID = 0;
		for( int i = 0; i < m_Sprites.size(); i++ )
		{
			if( m_Sprites[i]->textureID > m_GreatestTextureID )
			{
				lastHeighestTextureID = i - 1;
				break;
			}
			
			if( m_TextureArray[TEXTURE_ARRAY_SIZE32 - 1] == 0 )
				lastHeighestTextureID = i;
			
			if( i == m_Sprites.size() - 1 && (!m_Sprites[i]->textureID > m_GreatestTextureID ) )
				lastHeighestTextureID = i;
		}
		
		if( lastHeighestTextureID == m_Sprites.size() - 1 )
			everySpriteIsDrawn = true;
		
		m_RenderedSprites.clear();
		m_RenderedSprites.insert(m_RenderedSprites.begin(), m_Sprites.begin()+firstLowestTextureID, m_Sprites.begin()+lastHeighestTextureID+1);
	}
	
	void StaticSpriteRenderer::sendDataToGPU()
	{
		Vertex* vertexData = new Vertex [4 * m_RenderedSprites.size()];
		
		unsigned int x = 0;
		for( int i = 0; i < m_RenderedSprites.size(); i++ )
		{
			vertexData[ x ].setPosition( m_RenderedSprites[i]->x, m_RenderedSprites[i]->y, m_RenderedSprites[i]->z );
			vertexData[ x ].setColor( m_RenderedSprites[i]->col.r, m_RenderedSprites[i]->col.g, m_RenderedSprites[i]->col.b, m_RenderedSprites[i]->col.a );
			vertexData[ x ].setUV( 0.0f, 1.0f );
			vertexData[ x ].tid = (float)m_RenderedSprites[i]->textureID;
			
			vertexData[x+1].setPosition( m_RenderedSprites[i]->x + m_RenderedSprites[i]->w, m_RenderedSprites[i]->y, m_RenderedSprites[i]->z );
			vertexData[x+1].setColor( m_RenderedSprites[i]->col.r, m_RenderedSprites[i]->col.g, m_RenderedSprites[i]->col.b, m_RenderedSprites[i]->col.a );
			vertexData[x+1].setUV( 1.0f, 1.0f );
			vertexData[x+1].tid = (float)m_RenderedSprites[i]->textureID;
			
			vertexData[x+2].setPosition( m_RenderedSprites[i]->x, m_RenderedSprites[i]->y - m_RenderedSprites[i]->h, m_RenderedSprites[i]->z );
			vertexData[x+2].setColor( m_RenderedSprites[i]->col.r, m_RenderedSprites[i]->col.g, m_RenderedSprites[i]->col.b, m_RenderedSprites[i]->col.a );
			vertexData[x+2].setUV( 0.0f, 0.0f );
			vertexData[x+2].tid = (float)m_RenderedSprites[i]->textureID;
			
			vertexData[x+3].setPosition( m_RenderedSprites[i]->x + m_RenderedSprites[i]->w, m_RenderedSprites[i]->y - m_RenderedSprites[i]->h, m_RenderedSprites[i]->z );
			vertexData[x+3].setColor( m_RenderedSprites[i]->col.r, m_RenderedSprites[i]->col.g, m_RenderedSprites[i]->col.b, m_RenderedSprites[i]->col.a );
			vertexData[x+3].setUV( 1.0f, 0.0f );
			vertexData[x+3].tid = (float)m_RenderedSprites[i]->textureID;
			
			x += 4;
		}
		
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( Vertex ) * 4 * m_RenderedSprites.size(), &vertexData[0] );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		
		delete [] vertexData;
	}
	
	void StaticSpriteRenderer::clearTextureArray()
	{
		for( int i = 0; i < TEXTURE_ARRAY_SIZE32; i++ )
		{
			m_TextureArray[i] = 0;
		}
	}
	
	bool StaticSpriteRenderer::swapSprites( unsigned int key1, unsigned int key2 )
	{
		Sprite* tempSprite1;
		Sprite* tempSprite2;
		
		tempSprite1 = m_Sprites[key1];
		tempSprite2 = m_Sprites[key2];
		
		if( key1 > key2 )
		{
			m_Sprites.erase( m_Sprites.begin() + key1 );
			m_Sprites.insert( m_Sprites.begin() + key2, tempSprite1 );
			m_Sprites.erase( m_Sprites.begin() + key2 + 1 );
			m_Sprites.insert( m_Sprites.begin() + key1, tempSprite2 );
			
			return true;
		}
		else if( key2 > key1 )
		{
			m_Sprites.erase( m_Sprites.begin() + key2 );
			m_Sprites.insert( m_Sprites.begin() + key1, tempSprite2 );
			m_Sprites.erase( m_Sprites.begin() + key1 + 1 );
			m_Sprites.insert( m_Sprites.begin() + key2, tempSprite1 );
			
			return true;
		}
		
		return false;
	}
	
} }
