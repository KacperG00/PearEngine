#ifndef _PEAR_RESOURCE_MANAGER_H_
#define _PEAR_RESOURCE_MANAGER_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <vector>

#include "PEngine/graphics/font.h"
#include "PEngine/graphics/sprite.h"

namespace pear {
	
	class ResourceManager
	{
		// Keys are Renderable2D::id
		static std::map <unsigned long int, graphics::Renderable2D*> m_Renderables2D;
		static unsigned long int m_RenderableCount;
		
		// Keys are Texture::filename
		static std::map <std::string, graphics::Texture*> m_Textures;
		static unsigned int m_TextureCount;
		
		// Keys are Font::name
		static std::map <std::string, graphics::Font*> m_Fonts;
		static unsigned int m_FontCount;
		
	public:
		static void cleanManager();
		
		static void addTexture( const char* filename );
		static void addTexture( const char* name, graphics::Texture* texture );
		static void addFont( const char* filename );
		static void addRenderable2D( graphics::Renderable2D* renderable );
		
		static void deleteTexture( const char* filename );
		static void deleteFont( const char* filename );
		static void deleteRenderable2D( unsigned long int id );
		
		static graphics::Texture* getTexture( const char* texture_name );
		static graphics::Font* getFont( const char* font_name );
		
		static graphics::Renderable2D* getRenderable2D( unsigned int id );
		static graphics::Sprite* getSprite( unsigned int id );
		
		inline static unsigned int getTextureCount() { return m_TextureCount; }
		inline static unsigned int getFontCount() { return m_FontCount; }
		inline static unsigned int getRenderable2DCount() { return m_RenderableCount; }
		inline static unsigned int getSpriteCount() { return graphics::Sprite::sprite_count; }
		
		static void printRenderableInfo();
		
	private:
		static graphics::Texture* loadTexture( const char* filename );
		static graphics::Font* loadFont( const char* filename );
		static void mendRenderables2D();
		
		static void cleanRenderables2DMap();
		static void cleanTextureMap();
		static void cleanFontMap();
	};
	
}

#endif // _PEAR_RESOURCE_MANAGER_H_
