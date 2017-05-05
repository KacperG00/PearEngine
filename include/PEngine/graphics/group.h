#ifndef _PEAR_GRAPHICS_GROUP_H_
#define _PEAR_GRAPHICS_GROUP_H_

#include "PEngine/graphics/renderable2D.h"
#include "PEngine/graphics/transformation_types.h"

#include <vector>

namespace pear { namespace graphics {
	
	class Group : public Renderable2D
	{
	public:
		std::vector <Renderable2D*> renderables;
		unsigned int numberOfRenderables;
		
	private:
		glm::vec2 m_Origin;
		
	public:
		Group();
		~Group();
		void addToGroup( Renderable2D* renderable );
		
		void setOrigin( const glm::vec2& new_origin );
		
		void transform( PearTransformationType type, const glm::vec3& vector, float angle = 1.0f );
	};
	
} }

#endif // _PEAR_GRAPHICS_GROUP_H_
