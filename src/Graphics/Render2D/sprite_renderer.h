#ifndef PEAR_SPRITERENDERER_H
#define PEAR_SPRITERENDERER_H

#include "renderer2D.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sprite.h"
#include "spritesheet.h"
#include "../shader.h"

namespace pear { namespace graphics {
	
	const unsigned int PEAR_TRANSFORM_TRANSLATE = 1;
	const unsigned int PEAR_TRANSFORM_ROTATE = 2;
	const unsigned int PEAR_TRANSFORM_SCALE = 3;
	
	class SpriteRenderer : public Renderer2D
	{
		// Remove this as fast as posible :P
	public:
		static unsigned int WAIT;
		
	private:
		std::vector<Renderable2D*> m_Sprites;
		Shader m_Shader;
		unsigned int m_AttributeNum;
		
		GLuint m_IBO;
		
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void submit( Renderable2D* sprite ) override;
		void flush() override;
		
		void transformMatrix( unsigned int sprite_slot, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale, float angle = 1.0f );
		void transformMatrix( unsigned int sprite_slot, const glm::vec3& transformation, const unsigned int transformation_type, float angle = 1.0f );
		
	private:
		void initShaders();
		void initIBO();
		Sprite* loadSprite( Renderable2D* renderable );
		SpriteSheet* loadSpriteSheet( Renderable2D* renderable );
	};
	
} }

#endif // PEAR_SPRITERENDERER_H
