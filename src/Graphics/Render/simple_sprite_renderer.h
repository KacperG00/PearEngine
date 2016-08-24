#ifndef PEAR_SIMPLESPRITERENDERER_H
#define PEAR_SIMPLESPRITERENDERER_H

#include <vector>

#include <glm/glm.hpp>

#include "sprite.h"
#include "../shader.h"

namespace pear {
	
	const unsigned int MAX_SPRITES = 10000;
	const unsigned long int MAX_VERTICES = 4 * MAX_SPRITES;
	const unsigned long int MAX_ELEMENTS = 6 * MAX_SPRITES;
	const unsigned long int MAX_SIZE_OF_SPRITES = sizeof( Vertex ) * MAX_VERTICES;
	
	class SimpleSpriteRenderer
	{
		std::vector<Sprite*> sprites;
		Shader m_Shader;
		GLuint m_VBO;
		GLuint m_IBO;
		
	public:
		SimpleSpriteRenderer();
		~SimpleSpriteRenderer();
		void submit( Sprite* sprite );
		void flush();
		
	private:
		void initShaders();
	};
	
}

#endif // PEAR_SIMPLESPRITERENDERER_H
