#include "PEngine/app/resource_manager.h"

#include "PEngine/graphics/render.h"

#include "PEngine/utilities/string_manipulations.h"
#include "PEngine/utilities/error.h"
#include "PEngine/string_constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <string>

namespace pear {
	
	// RENDERABLES DATA //
	std::map <unsigned long int, graphics::Renderable2D*> ResourceManager::m_Renderables2D;
	unsigned long int ResourceManager::m_RenderableCount = 0;
	
	// TEXTURES DATA //
	std::map <std::string, graphics::Texture*> ResourceManager::m_Textures;
	unsigned int ResourceManager::m_TextureCount = 0;
	
	// FONTS DATA //
	std::map <std::string, graphics::Font*> ResourceManager::m_Fonts;
	unsigned int ResourceManager::m_FontCount = 0;
	
	void ResourceManager::cleanManager()
	{
		cleanRenderables2DMap();
		cleanFontMap();
		cleanTextureMap();
	}
	
	void ResourceManager::addTexture( const char* filename )
	{
		m_Textures.insert( std::pair<std::string, graphics::Texture*>( filename, loadTexture( filename ) ) );
		m_TextureCount++;
	}
	
	void ResourceManager::addTexture( const char* name, graphics::Texture* texture )
	{
		m_Textures.insert( std::pair<std::string, graphics::Texture*>( name, texture ) );
		m_TextureCount++;
	}
	
	void ResourceManager::addFont( const char* filename )
	{
		graphics::Font* font = loadFont( filename );
		if( font != nullptr )
		{
			m_Fonts.insert( std::pair<std::string, graphics::Font*>( filename, font ) );
			m_FontCount++;
		}
	}
	
	void ResourceManager::addRenderable2D( graphics::Renderable2D* renderable )
	{
		m_RenderableCount++;
		renderable->id = m_RenderableCount;
		m_Renderables2D.insert( std::pair<unsigned long int, graphics::Renderable2D*>( m_RenderableCount, renderable ) );
	}
	
	void ResourceManager::deleteTexture( const char* filename )
	{
		glDeleteTextures( 1, &m_Textures[filename]->textureID );
		delete m_Textures[filename];
		m_Textures.erase( filename );
		m_TextureCount--;
	}
	
	void ResourceManager::deleteFont( const char* filename )
	{
		delete m_Fonts[filename];
		m_Fonts.erase( filename );
		m_FontCount--;
	}
	
	void ResourceManager::deleteRenderable2D( unsigned long int id )
	{
		if( m_Renderables2D[id]->renderer != NULL )
		{
			m_Renderables2D[id]->renderer->erase( m_Renderables2D[id] );
		}
		
		unsigned long int biggestID = m_Renderables2D.cend()->first;
		
		// swaping deleting element with last one in the map
		std::swap(m_Renderables2D[id], m_Renderables2D[biggestID]);
		
		// updating id of renderable from the end of map
		m_Renderables2D[id]->id = id;
		
		// deleting last element
		delete m_Renderables2D[biggestID];
		m_Renderables2D.erase( biggestID );
		
		m_RenderableCount--;
	}
	
	graphics::Texture* ResourceManager::loadTexture( const char* filename )
	{
		graphics::Texture* texture = new graphics::Texture;
		
		SDL_Surface* image = nullptr;
		
		image = IMG_Load( std::string( paths_from_build::TEXTURES + filename ).c_str() );
		if( image == NULL )
			utils::printError("Failed to load image %s\n", filename);
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
			
			glGenTextures( 1, &texture->textureID );
			glBindTexture( GL_TEXTURE_2D, texture->textureID );
			
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			
			glTexImage2D(	GL_TEXTURE_2D, 0, imageFormat, image->w, image->h, 0, imageFormat,
							GL_UNSIGNED_BYTE, image->pixels );
			glGenerateMipmap( GL_TEXTURE_2D );
			
			glBindTexture( GL_TEXTURE_2D, 0 );
			
			texture->width = image->w;
			texture->height = image->h;
			
			texture->filename = filename;
			
			SDL_FreeSurface( image );
			image = nullptr;
		}
		
		return texture;
	}
	
	graphics::Font* ResourceManager::loadFont( const char* filename )
	{
		graphics::Font* font = new graphics::Font(filename);
		if( font->getBitmap(16) == nullptr )
		{
			delete font;
			font = nullptr;
		}
		
		return font;
	}
	
	graphics::Texture* ResourceManager::getTexture( const char* texture_name )
	{
		if( m_Textures.count(texture_name) == 0 )
		{
			utils::printError("Failed to find texture: %s", texture_name);
			return NULL;
		}
		else
			return m_Textures[texture_name];
	}
	
	graphics::Font* ResourceManager::getFont( const char* font_name )
	{
		if( m_Fonts.count(font_name) == 0 )
			return nullptr;
		else
			return m_Fonts[font_name];
	}
	
	graphics::Renderable2D* ResourceManager::getRenderable2D( unsigned int id )
	{
		if( m_Renderables2D.count(id) == 0 )
			return nullptr;
		else
			return m_Renderables2D[id];
	}
	
	graphics::Sprite* ResourceManager::getSprite( unsigned int id )
	{
		if( m_Renderables2D.count(id) == 0 )
			return nullptr;
		else
			return (graphics::Sprite*)m_Renderables2D[id];
	}
	
	void ResourceManager::printRenderableInfo()
	{
		std::cout << "______Renderable_INFO______" << std::endl;
		std::cout << "Number of renderables: " << m_RenderableCount << std::endl;
		std::cout << std::endl;
		
		int x = 1;
		for( auto const& i : m_Renderables2D )
		{
			std::cout << m_Renderables2D.count(x++) << " renderables have id: " << i.second->id << std::endl;
		}
	}
	
	void ResourceManager::cleanRenderables2DMap()
	{
		std::cerr << "Releasing renderable2D data... ";
		
		if( !m_Renderables2D.empty() )
		{
			for( auto const& i : m_Renderables2D )
			{
				if( i.second->renderableType != graphics::Renderable2D::RenderableType::GROUP )
				{
					if( i.second->renderer != nullptr )
						i.second->renderer->erase( i.second );
				}
				
				delete i.second;
			}
			m_Renderables2D.clear();
		}
		
		if( m_Renderables2D.empty() )
			std::cerr << "Success\n";
		else
			std::cerr << "Failed\n";
	}
	
	void ResourceManager::cleanTextureMap()
	{
		if( !(m_Textures.empty()) )
		{
			std::cerr << "Releasing texture data... ";
			for( auto const& i : m_Textures )
				glDeleteTextures( 1, &(i.second->textureID) );
				
			m_Textures.clear();
			
			if(m_Textures.empty())
				std::cerr << "Success\n";
			else
				std::cerr << "Failed\n";
		}
    }
    
    void ResourceManager::cleanFontMap()
    {
		if( !(m_Fonts.empty()) )
		{
			std::cerr << "Releasing font data... ";
			
			m_Fonts.clear();
			
			if(m_Fonts.empty())
				std::cerr << "Success\n";
			else
				std::cerr << "Failed\n";
		}
	}
	
}
