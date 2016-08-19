#ifndef PEAR_SIMPLESPRITERENDERER_H
#define PEAR_SIMPLESPRITERENDERER_H

#include <vector>

#include "sprite.h"

namespace pear {
	
	class SimpleSpriteRenderer
	{
		std::vector<Sprite*> sprites;
		GLuint m_VBO;
		GLuint m_IBO;
		
		unsigned int spritesCount;
		
	public:
		SimpleSpriteRenderer();
		~SimpleSpriteRenderer();
		void submit( Sprite* sprite );
		void flush();
	};
	
}

#endif // PEAR_SIMPLESPRITERENDERER_H
