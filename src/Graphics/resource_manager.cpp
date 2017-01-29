#include "resource_manager.h"

#include "../Utilities/string_manipulations.h"
#include "../string_constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

namespace pear { namespace graphics {
	
	std::map <unsigned int, Sprite*> ResourceManager::m_Sprites;
	unsigned int ResourceManager::m_SpriteCount = 0;
	std::map <std::string, Texture*> ResourceManager::m_Textures;
	unsigned int ResourceManager::m_TextureCount = 0;
	std::map <std::string, Font*> ResourceManager::m_Fonts;
	unsigned int ResourceManager::m_FontCount = 0;
	
	void ResourceManager::cleanManager()
	{
		cleanTextureMap();
		cleanFontMap();
	}
	
	void ResourceManager::addTexture( const char* filename )
	{
		m_Textures.insert( std::pair<std::string, Texture*>( filename, loadTexture( filename ) ) );
		m_TextureCount++;
	}
	
	void ResourceManager::addFont( const char* filename )
	{
#if true
		Font* font = loadFont( filename );
		m_Fonts.insert( std::pair<std::string, Font*>( filename, font ) );
		m_FontCount++;
		
		// Test if fonts work
		m_Textures.insert( std::pair<std::string, Texture*>( filename, font->texture ) );
		m_TextureCount++;
#else
		m_Fonts.insert( std::pair<std::string, Font*>( filename, loadFont( filename ) ) );
		m_FontCount++;
#endif
	}
	
	void ResourceManager::addSprite( Sprite* sprite )
	{
		if( getSpriteCount() > 0 )
		{
			for( unsigned int i = 1; i <= m_Sprites.size(); i++ )
			{
				try
				{
					m_Sprites.at(i)->spriteID = i+1;
				}
				catch(const std::out_of_range& oor)
				{
					std::cerr << "Out of range error: " << oor.what() << std::endl;
				}
			}
		}
		
		unsigned int currSpriteID = m_Sprites.size() + 1;
		
		m_Sprites.insert( std::pair<unsigned int, Sprite*>( currSpriteID, sprite ) );
		m_Sprites.at(currSpriteID)->spriteID = currSpriteID;
		m_SpriteCount++;
	}
	
	Texture* ResourceManager::loadTexture( const char* filename )
	{
		Texture* texture = nullptr;
		
		SDL_Surface* image = nullptr;
		
		image = IMG_Load( std::string( paths_from_build::TEXTURES + filename ).c_str() );
		if( image == NULL )
			std::cout << "Failed to load image " << filename << std::endl;
		else
		{
			unsigned int imageFormat = 0;
			utils::FileExtention extention = utils::getFileExtention( filename );
			switch( extention )
			{
				case utils::FileExtention::PNG:
					imageFormat = GL_RGBA;
					break;
				default:
					imageFormat = GL_RGB;
					break;
			}
			
			texture = from_SDL_Surface_to_Texture(image, imageFormat);
			texture->filename = filename;
			
			SDL_FreeSurface( image );
			image = nullptr;
		}
		
		return texture;
	}
	
	Font* ResourceManager::loadFont( const char* filename )
	{
		Font* font = new Font;
		TTF_Font* ttf_font = nullptr;
		SDL_Surface* bitmap = nullptr;
		
		font->name = filename;
		
		ttf_font = TTF_OpenFont( std::string( paths_from_build::FONTS + filename ).c_str(), 128 );
		if( ttf_font == NULL )
			printf( "Failed to load font: %s\n", filename );
		else
		{
			SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
			bitmap = TTF_RenderText_Blended( ttf_font, "nice amigo", color );
			font->texture = from_SDL_Surface_to_Texture(bitmap, GL_RGBA);
		}
		
		return font;
	}
	
	Texture* ResourceManager::getTexture( const char* texture_name )
	{
		if( m_Textures.count(texture_name) == 0 )
			return NULL;
		else
			return m_Textures[texture_name];
	}
	
	Sprite* ResourceManager::getSprite( unsigned int element )
	{
		if( m_Sprites.count(element) == 0 )
			return NULL;
		else
			return m_Sprites[element];
	}
	
	void ResourceManager::cleanTextureMap()
	{
		if( !(m_Textures.empty()) )
		{
			printf("Releasing texture data... ");
			for( auto const& i : m_Textures )
				glDeleteTextures( 1, &(i.second->textureID) );
				
			m_Textures.clear();
			
			if(m_Textures.empty())
				printf("Success\n");
		}
    }
    
    void ResourceManager::cleanFontMap()
    {
		if( !(m_Fonts.empty()) )
		{
			printf("Releasing font data... ");
			for( auto const& i : m_Fonts )
				glDeleteTextures( 1, &(i.second->texture->textureID) );
			
			m_Fonts.clear();
			
			if(m_Fonts.empty())
				printf("Success\n");
		}
	}
	
	Texture* ResourceManager::from_SDL_Surface_to_Texture( SDL_Surface* surface, unsigned int image_format )
	{
		Texture* texture = new Texture;
		texture->textureID = 0;
		
		if( texture->textureID != 0 )
			glDeleteTextures( 1, &texture->textureID );
		
		glGenTextures( 1, &texture->textureID );
		glBindTexture( GL_TEXTURE_2D, texture->textureID );
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		
		glTexImage2D( GL_TEXTURE_2D, 0, image_format, surface->w, surface->h, 0, image_format, GL_UNSIGNED_BYTE, surface->pixels );
		glGenerateMipmap( GL_TEXTURE_2D );
		
		glBindTexture( GL_TEXTURE_2D, 0 );
		
		texture->width = surface->w;
		texture->height = surface->h;
		
		return texture;
	}
	
} }
