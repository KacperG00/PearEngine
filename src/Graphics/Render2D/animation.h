#ifndef PEAR_2DRENDERING_ANIMATION_H
#define PEAR_2DRENDERING_ANIMATION_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace pear { namespace graphics {
	
	class SS_Animation
	{
	private:
		const char* m_Name;
		
		std::vector<glm::vec4> m_NormPos;
		unsigned int m_CountOfFrames;
		unsigned int m_NumOfCurrFrame;
		glm::vec4* m_CurrFrame;
		
	public:
		SS_Animation(const char* texture_name, int nosh, int nosv, int first_sprite, int last_sprite);
		SS_Animation(const char* texture_name, const char* animation_name);
		~SS_Animation();
		
		void resetAni();
		
		glm::vec4* getFrame();
		glm::vec4* getFrame(unsigned int frame_number);
		const char* getName();
		
	private:
		std::vector<glm::vec4> loadDataRegDim(const char* texture_name, int nosh, int nosv, int first_sprite, int last_sprite);
		std::vector<glm::vec4> loadDataWithSP(const char* filename, const char* animationName);
		std::vector<glm::vec4> normalizePositions(const char* texture_name, const std::vector<glm::vec4>&);
	};
	
} }

#endif // PEAR_2DRENDERING_ANIMATION_H
