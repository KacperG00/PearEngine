#ifndef _PEAR_GRAPHICS_LABEL_H_
#define _PEAR_GRAPHICS_LABEL_H_

#include "PEngine/graphics/renderer2D.h"
#include "PEngine/graphics/group.h"
#include "PEngine/graphics/sprite.h"
#include "PEngine/graphics/font.h"

#include <string>
#include <vector>

namespace pear { namespace graphics {
	
	class Label : public Group
	{
	public:
		std::string text;
		Color textColor;
		
	private:
		Font* m_Font;
		unsigned int m_FontResolution;
		Texture* m_Bitmap;
		
	public:
		Label(const glm::vec2& pos, const char* font, unsigned int font_resolution, float depth = 0.0f);
		~Label();
		
		void setResolution( unsigned int res );
		void setText( const char* format, ... );
		void write( const char* format, ... );
		
		// sets color not for currently generated glyphs, but for new ones
		void setTextColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		
		void setGlyphsColor( int first, int last,
							unsigned char r, unsigned char g, unsigned char b, unsigned char a );
		
	private:
		void generateNewSpritesAtTheEndOfString( const char* text );
		Sprite* generateSprite( unsigned char unicode, float &advance_x, float &advance_y );
	};
	
} }

#endif // _PEAR_GRAPHICS_LABEL_H_
