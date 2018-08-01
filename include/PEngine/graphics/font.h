#ifndef _PEAR_GRAPHICS_FONT_H_
#define _PEAR_GRAPHICS_FONT_H_

#include "PEngine/graphics/renderable2D.h"

#include <SDL2/SDL.h>

#include <vector>

namespace pear { namespace graphics {
	
#define PEAR_FONT_MAX_GLYPHS 256
#define PEAR_FONT_MAX_RESOLUTION 129
	
	struct Glyph
	{
		glm::vec4 uv;
		
		// should be unique for every bitmap (resolution)
		unsigned int width;
		unsigned int height;
	};
	
	class Font
	{
	public:
		const char* name;
		Glyph glyphs[PEAR_FONT_MAX_GLYPHS];
		
	private:
		struct Font_Bitmap
		{
			Texture* bitmap;
			bool rendered;
		};
		
		Font_Bitmap m_Bitmaps[PEAR_FONT_MAX_RESOLUTION];
		
	public:
		Font(const char* filename);
		~Font();
		
		Texture* getBitmap( unsigned int font_resolution );
		
	private:
		void loadBitmapWithResolution( unsigned int res );
		void from_SDL_Surface_to_Texture( SDL_Surface* surface, Texture* texture, unsigned int image_format );
	};
	
} }

#endif // _PEAR_GRAPHICS_FONT_H_
