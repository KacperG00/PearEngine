#include "resource_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

namespace pear {
	
	std::map <std::string, GLuint> ResourceManager::m_Textures;
	GLuint ResourceManager::m_TextureCount = 0;
	
	void ResourceManager::cleanManager()
	{
		std::map<std::string, unsigned int>::iterator it = m_Textures.begin();
		for( it = m_Textures.begin(); it != m_Textures.end(); it++ )
			glDeleteTextures( 1, &(it->second) );
	}
	
	void ResourceManager::addTexture( const char* filename )
	{
		m_Textures.insert( std::pair<std::string, GLuint>( filename, loadTexture( filename ) ) );
		m_TextureCount++;
	}
	
	GLuint ResourceManager::loadTexture( const char* filename )
	{
		GLuint textureID = 0;
		
		SDL_Surface* image = IMG_Load( std::string( std::string("../src/Graphics/Render/Textures/") + filename ).c_str() );
		if( image == NULL )
			std::cout << "Failed to load image " << filename << std::endl;
		else
		{
			if( textureID != 0 )
				glDeleteTextures( 1, &textureID );
			
			glGenTextures( 1, &textureID );
			glBindTexture( GL_TEXTURE_2D, textureID );
			
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
			glGenerateMipmap( GL_TEXTURE_2D );
			
			glBindTexture( GL_TEXTURE_2D, 0 );
			
			SDL_FreeSurface( image );
			image = nullptr;
		}
		
		return textureID;
	}
	
}
