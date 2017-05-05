#include "PEngine/graphics/font.h"

#include "PEngine/string_constants.h"
#include "PEngine/utilities/error.h"

#include "PEngine/app/resource_manager.h"

#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

namespace pear { namespace graphics {
	
	Font::Font( const char* filename )
		: name( filename )
	{
		getBitmap( 16 );
	}
	
	Font::~Font()
	{
		for( unsigned int i = 0; i < PEAR_FONT_MAX_RESOLUTION; ++i )
		{
			if( m_Bitmaps[i].rendered )
				ResourceManager::deleteTexture( m_Bitmaps[i].bitmap->filename.c_str() );
		}
	}
	
	Texture* Font::getBitmap( unsigned int font_resolution )
	{
		if( !m_Bitmaps[font_resolution].rendered )
		{
			m_Bitmaps[font_resolution].bitmap = new Texture;
			m_Bitmaps[font_resolution].bitmap->filename =	( std::string(name)
															+ ".texture"
															+ std::to_string(font_resolution)).c_str();
			m_Bitmaps[font_resolution].bitmap->textureID = 0;
			
			loadBitmapWithResolution( font_resolution );
			
			m_Bitmaps[font_resolution].rendered = true;
		}
		
		return m_Bitmaps[font_resolution].bitmap;
	}
	
	void Font::loadBitmapWithResolution( unsigned int res )
	{
		TTF_Font* ttf_font = nullptr;
		
		SDL_Surface* bitmap = nullptr;
		unsigned int bitmap_width = 0;
		unsigned int bitmap_height = 0;
		
		std::vector <SDL_Surface*> gs;
		
		SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
		
		ttf_font = TTF_OpenFont( std::string( paths_from_build::FONTS + name ).c_str(), res );
		if( ttf_font == nullptr )
		{
			utils::printError( "Failed to load font: %s\n", name );
			m_Bitmaps[res].bitmap = nullptr;
		}
		else
		{
			//
			// Rendering glyph by glyph in separated SDL_Surfaces from ttf file
			//
			int posx = 0;
			
			for( uint16_t i = 31; i < PEAR_FONT_MAX_GLYPHS; ++i )
			{
				if( TTF_GlyphIsProvided(ttf_font, i) > 0 )
				{
					SDL_Surface* surface = nullptr;
					
					const char* c = (std::string("") + (char)i).c_str();
					
					surface = TTF_RenderText_Blended( ttf_font, c, color );
					gs.push_back(surface);
					
					glyphs[i].width = surface->w;
					glyphs[i].height = surface->h;
					
					glyphs[i].uv.x = (float)posx;
					
					posx += surface->w;
				}
			}
			
			TTF_CloseFont(ttf_font);
			
			//
			// Creating one bitmap with all of signs in it
			// 
			for( unsigned int i = 0; i < gs.size(); ++i )
			{
				bitmap_width += gs[i]->w;
				
				if( bitmap_height < gs[i]->h )
				{
					bitmap_height = gs[i]->h;
				}
			}
			
			const SDL_PixelFormat& fmt = *(gs[0]->format);
			bitmap = SDL_CreateRGBSurface( 	0, bitmap_width, bitmap_height,
											fmt.BitsPerPixel,
											fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask );
			
			int destination_pos_x = 0;
			
			for( unsigned int i = 0; i < gs.size(); ++i )
			{
				SDL_Rect srcrect;
				SDL_Rect desrect;
				
				srcrect.x = 0;
				srcrect.y = 0;
				srcrect.w = gs[i]->w;
				srcrect.h = gs[i]->h;
				
				desrect.x = destination_pos_x;
				desrect.y = 0;
				desrect.w = gs[i]->w;
				desrect.h = gs[i]->h;
				
				destination_pos_x += gs[i]->w;
				
				SDL_BlitSurface( gs[i], &srcrect, bitmap, &desrect );
			}
			
			//
			// Counting glyphs' uvs
			//
			for( uint16_t i = 0; i < PEAR_FONT_MAX_GLYPHS; ++i )
			{
				glyphs[i].uv = glm::vec4(
									(float)(glyphs[i].uv.x/(double)(bitmap_width)),
									1.0 - (double)(glyphs[i].height) / (double)(bitmap_height),
									(float)(glyphs[i].uv.x+(float)glyphs[i].width)/(double)(bitmap_width),
									1.0f );
			}
			
			for( int i = gs.size() - 1; i >= 0; --i )
			{
				SDL_FreeSurface( gs[i] );
				gs.erase( gs.begin() + i );
			}
			
			from_SDL_Surface_to_Texture( bitmap, m_Bitmaps[res].bitmap, GL_RGBA );
			ResourceManager::addTexture( m_Bitmaps[res].bitmap->filename.c_str(), m_Bitmaps[res].bitmap );
		}
	}
	
	void Font::from_SDL_Surface_to_Texture( SDL_Surface* surface, Texture* texture, unsigned int image_format )
	{
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
	}
	
} }
