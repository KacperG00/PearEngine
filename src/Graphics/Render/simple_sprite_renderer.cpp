#include "simple_sprite_renderer.h"

#include "../resource_manager.h"

#include <iostream>

namespace pear {
	
	SimpleSpriteRenderer::SimpleSpriteRenderer()
		: m_VBO( 0 ), m_IBO( 0 )
	{
		initShaders();
		
		glGenBuffers( 1, &m_VBO );
		glGenBuffers( 1, &m_IBO );
		
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferData( GL_ARRAY_BUFFER, MAX_VERTICES * sizeof( Vertex ), NULL, GL_STATIC_DRAW );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position) );
		glVertexAttribPointer( 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color) );
		glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tid) );
		glVertexAttribPointer( 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv) );
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
	
	SimpleSpriteRenderer::~SimpleSpriteRenderer()
	{
		if( m_VBO )
			glDeleteBuffers( 1, &m_VBO );
		if( m_IBO )
			glDeleteBuffers( 1, &m_IBO );
			
		for( int i = 0; i < sprites.size(); i++ )
			sprites.pop_back();
	}
	
	void SimpleSpriteRenderer::submit(Sprite* sprite)
	{
		Vertex vertexData[4];
		vertexData[0].setPosition( sprite->x, sprite->y, 0.0f );
		vertexData[0].setColor( sprite->col.r, sprite->col.g, sprite->col.b, sprite->col.a );
		vertexData[0].setUV( 0.0f, 1.0f );
		vertexData[0].tid = (float)sprite->textureID;
		
		vertexData[1].setPosition( sprite->x + sprite->w, sprite->y, 0.0f );
		vertexData[1].setColor( sprite->col.r, sprite->col.g, sprite->col.b, sprite->col.a );
		vertexData[1].setUV( 1.0f, 1.0f );
		vertexData[1].tid = (float)sprite->textureID;
		
		vertexData[2].setPosition( sprite->x, sprite->y - sprite->h, 0.0f );
		vertexData[2].setColor( sprite->col.r, sprite->col.g, sprite->col.b, sprite->col.a );
		vertexData[2].setUV( 0.0f, 0.0f );
		vertexData[2].tid = (float)sprite->textureID;
		
		vertexData[3].setPosition( sprite->x + sprite->w, sprite->y - sprite->h, 0.0f );
		vertexData[3].setColor( sprite->col.r, sprite->col.g, sprite->col.b, sprite->col.a );
		vertexData[3].setUV( 1.0f, 0.0f );
		vertexData[3].tid = (float)sprite->textureID;
		
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferSubData( GL_ARRAY_BUFFER, sizeof( vertexData ) * sprites.size(), sizeof( vertexData ), &vertexData );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		
		sprites.push_back( sprite );
	}
	
	void SimpleSpriteRenderer::flush()
	{
		m_Shader.use();
		
		GLint textures[16];
		for( int i = 0; i < 16; i++ )
		{
			glActiveTexture( GL_TEXTURE0 + i );
			textures[i] = i;
			glBindTexture( GL_TEXTURE_2D, i+1 );
		}
		
		glUniform1iv(m_Shader.getUniformLocation("textures"), 16, textures);
		
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glDrawElements( GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		
		m_Shader.unuse();
	}
	
	void SimpleSpriteRenderer::initShaders()
	{
		m_Shader.compileShaders( "sprite_shader" );
		m_Shader.addAttribute( "vsPosition" );
		m_Shader.addAttribute( "vsColor" );
		m_Shader.addAttribute( "vsTextureID" );
		m_Shader.addAttribute( "vsTextureCoords" );
		m_Shader.linkShaders();
	}
	
}
