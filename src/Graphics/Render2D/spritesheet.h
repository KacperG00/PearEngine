#ifndef PEAR_GRAPHICS_SPRITESHEET_H
#define PEAR_GRAPHICS_SPRITESHEET_H

#include "renderable2D.h"
#include "animation.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace pear { namespace graphics {
	
	class SpriteSheet : public Renderable2D
	{
	private:
		int currAnimation;
		glm::vec4* currFrame;
		
	public:
		unsigned int spriteSheetID;
		
		std::vector<SS_Animation> animations;
		
	public:
		SpriteSheet( const glm::vec4& pos_and_dim, const char* texture_name, float depth = 0.0f );
		~SpriteSheet();
		
		bool ready();
		
		glm::vec4* getCurrFrame();
		void nextFrame();
		
		void startAnimation(unsigned int ani_num);
		void addAnimationWithRegDim(int nosh, int nosv, int first_sprite, int last_sprite);
		void addAnimationWithSP(const char* animation_name);
	};
	
} }

#endif // PEAR_GRAPHICS_SPRITESHEET_H
