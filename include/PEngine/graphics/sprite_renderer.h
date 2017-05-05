#ifndef PEAR_SPRITERENDERER_H
#define PEAR_SPRITERENDERER_H

#include "PEngine/graphics/renderer2D.h"
#include "PEngine/graphics/transformation_types.h"
#include "PEngine/graphics/sprite.h"
#include "PEngine/graphics/spritesheet.h"
#include "PEngine/graphics/shader.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pear { namespace graphics {
	
	class SpriteRenderer : public Renderer2D
	{
	public:
		
		
	private:
		std::vector<Renderable2D*> m_Sprites;
		Shader m_Shader;
		unsigned int m_AttributeNum;
		
		GLuint m_IBO;
		
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void submit( Renderable2D* renderable ) override;
		void erase( Renderable2D* renderable ) override;
		void flush() override;
				
	private:
		void initShaders();
		void initIBO();
		Sprite* loadSprite( Renderable2D* renderable );
		SpriteSheet* loadSpriteSheet( Renderable2D* renderable );
	};
	
} }

#endif // PEAR_SPRITERENDERER_H
