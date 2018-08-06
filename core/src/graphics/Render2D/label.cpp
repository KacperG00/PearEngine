#include "PEngine/graphics/label.h"

#include "PEngine/app/application.h"
#include "PEngine/app/resource_manager.h"
#include "PEngine/utilities/error.h"

#include <cstring>

namespace pear { namespace graphics {
	
	Label::Label(const glm::vec2& pos, const char* font, unsigned int font_resolution, float depth)
		: Group(),
		m_Font( nullptr ), m_FontResolution( 0 ), m_Bitmap( nullptr ),
		text( "text" )
	{
		this->x = pos.x;
		this->y = pos.y;
		
		if(!(font_resolution < PEAR_FONT_MAX_RESOLUTION))
			font_resolution = 16;
		
		m_Font = ResourceManager::getFont( font );
		if( m_Font != nullptr )
		{
			setResolution( font_resolution );
			setTextColor( 0xFF, 0xFF, 0xFF, 0xFF );
			setText( text.c_str() );
		}
	}
	
	Label::~Label()
	{
		while( renderables.size() > 0 )
		{
			ResourceManager::deleteRenderable2D( renderables[0]->id );
			renderables.erase( renderables.begin() );
			numberOfRenderables--;
		}
	}
	
	void Label::setResolution( unsigned int res )
	{
		if(res < PEAR_FONT_MAX_RESOLUTION)
		{
			m_FontResolution = res;
			m_Bitmap = m_Font->getBitmapT( res );
			setText(text.c_str());
		}
	}
	
	void Label::setText( const char* format, ... )
	{
		if( m_Font == nullptr )
			utils::printError( "Failed to set label text (no font attached)!\n" );
		else if( !m_FontResolution )
			utils::printError( "In font \"%s\" resolution is equal 0!", m_Font->name );
		else
		{
			// creating a complete text string
			char txt[1024];
			
			va_list ap;
			va_start( ap, format );
			vsprintf( txt, format, ap );
			va_end( ap );
			
			// deleting previous text
			if(renderables.size() > 0)
			{
				for( int i = renderables.size()-1; i >= 0; --i )
				{
					ResourceManager::deleteRenderable2D( renderables[i]->id );
					renderables.pop_back();
					numberOfRenderables--;
				}
			}
			
			// creating new text
			text = txt;
			generateNewSpritesAtTheEndOfString(text.c_str());
		}
	}
	
	//       Wrong positioning in function generateNewSpritesAtTheEndOfString()
	//       There's no problem if the function works with setText()
	void Label::write( const char* format, ... )
	{
		// creating a complete text string
		char txt[1024];
		
		va_list ap;
		va_start( ap, format );
		vsprintf( txt, format, ap );
		va_end( ap );
		
		generateNewSpritesAtTheEndOfString( txt );
	}
	
	void Label::setTextColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	{
		this->textColor.set( r, g, b, a);
	}
	
	void Label::setGlyphsColor( int first, int last,
								unsigned char r, unsigned char g, unsigned char b, unsigned char a )
	{
		if( first < renderables.size() && last < renderables.size() )
		{
			Color color;
			color.set( r, g, b, a );
			
			for( int i = first; i <= last; ++i )
			{
				((Sprite*)renderables[i])->col = color;
			}
		}
	}
	
	// Doesn't work with Label::write()
	void Label::generateNewSpritesAtTheEndOfString( const char* text )
	{
		std::string txt = text;
		
		float advance_x = 0.0f;
		float advance_y = 0.0f;
		
		if( numberOfRenderables > 0 )
		{
			advance_x = renderables[numberOfRenderables-1]->x + renderables[numberOfRenderables-1]->w;
			advance_y = renderables[numberOfRenderables-1]->y;
		}
		
		Sprite* new_sprite = nullptr;
		
		for( int i = 0; i < txt.size(); ++i )
		{
			new_sprite = generateSprite( txt[i], advance_x, advance_y );
			
			if( new_sprite != nullptr )
			{
				addToGroup( new_sprite );
				new_sprite->col = textColor;
			}
		}
		
		// submitting text to it's renderer
		int renderables_size = numberOfRenderables;
		int txt_size = txt.size();
		int diff = renderables_size - txt_size;
		
		if( renderer != nullptr )
		{
			for( int i = renderables_size - 1; i >= diff; --i )
			{
				renderer->submit(renderables[i]);
			}
		}
	}
	
	Sprite* Label::generateSprite( unsigned char unicode, float &advance_x, float &advance_y )
	{
		int window_width = App::getWindow()->getWidth();
		int window_height = App::getWindow()->getHeight();
		
		float height = (float)(m_Font->getBitmap(m_FontResolution).height) / (float)window_height;
		
		Glyph * glyphs = m_Font->getBitmap(m_FontResolution).glyphs;
		
		if( unicode > 31 )
		{
			float width = (float)glyphs[unicode].width / (float)window_width;
			float height = (float)glyphs[unicode].height / (float)window_height;
			
			glm::vec4 pos_dim(this->x + advance_x, this->y + advance_y, width, height);
			
			advance_x += width;
		
			Sprite* sprite = new Sprite(pos_dim,
										m_Bitmap->filename.c_str(),
										glyphs[unicode].uv);
		
			return sprite;
		}
		else if( unicode == 10 )
		{
			advance_x = 0.0f;
			advance_y -= height;
		}
		
		return nullptr;
	}
	
} }
