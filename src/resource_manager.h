#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <map>
#include <vector>

#include "Graphics/Render2D/sprite.h"

namespace pear { namespace graphics {
	
	class ResourceManager
	{
		static std::map <unsigned int, Sprite*> m_Sprites;
		static unsigned int m_SpriteCount;
		
		static std::map <std::string, Texture*> m_Textures;
		static unsigned int m_TextureCount;
		
		static std::map <std::string, Font*> m_Fonts;
		static unsigned int m_FontCount;
		
	public:
		static void cleanManager();
		
		static void addTexture( const char* filename );
		static void addFont( const char* filename );
		static void addSprite( Sprite* );
		
		static Texture* getTexture( const char* texture_name );
		static Sprite* getSprite( unsigned int element );
		
		inline static GLuint getTextureCount() { return m_TextureCount; }
		inline static GLuint getSpriteCount() { return m_SpriteCount; }
		
	private:
		static Texture* loadTexture( const char* filename );
		static Font* loadFont( const char* filename );
		
		static void cleanTextureMap();
		static void cleanFontMap();
		
		static Texture* from_SDL_Surface_to_Texture( SDL_Surface* surface, unsigned int image_format );
	};
	
} }

#endif // RESOURCE_MANAGER_H
