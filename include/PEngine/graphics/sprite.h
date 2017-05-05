#ifndef PEAR_GRAPHICS_SPRITE_H
#define PEAR_GRAPHICS_SPRITE_H

#include "PEngine/graphics/renderable2D.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace pear { namespace graphics {
	
	class Sprite : public Renderable2D
	{
	public:
		Color col;
		GLuint textureID;
		
		bool sorted;
		
		static unsigned int sprite_count;
		
	public:
		Sprite( const glm::vec4& position_dimensions, const glm::ivec4& color, float depth = 0.0f );
		
		Sprite( const glm::vec4& position_dimensions, const char* texture_name, float depth = 0.0f );
		
		Sprite( const glm::vec4& position_dimensions, const char* texture_name,
				const glm::vec4& UV,
				float depth = 0.0f );
		
		~Sprite();
	};
	
} }

#endif // PEAR_GRAPHICS_SPRITE_H
