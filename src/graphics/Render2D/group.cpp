#include "PEngine/graphics/group.h"

#include "PEngine/app/resource_manager.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace pear { namespace graphics {
	
	Group::Group()
		: Renderable2D( RenderableType::GROUP, glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f ) ),
		numberOfRenderables( 0 )
	{
		setOrigin( glm::vec2( 0.0f, 0.0f ) );
	}
	
	Group::~Group()
	{
		while( numberOfRenderables > 0 )
		{
			ResourceManager::deleteRenderable2D( renderables[0]->id );
			renderables.erase( renderables.begin() );
			numberOfRenderables--;
		}
	}
	
	void Group::addToGroup( Renderable2D* renderable )
	{
		renderables.push_back( renderable );
		numberOfRenderables++;
	}
	
	void Group::setOrigin( const glm::vec2& new_origin )
	{
		m_Origin = new_origin;
	}
	
	void Group::transform( PearTransformationType type, const glm::vec3& vector, float angle )
	{
		glm::vec2 difference(0.0f, 0.0f);
		
		switch( type )
		{
			case PEAR_TRANSFORM_TRANSLATE:
				transMat = glm::translate( transMat, vector );
				break;
			case PEAR_TRANSFORM_ROTATE:
				rotationMat = glm::rotate( rotationMat, glm::radians(angle), vector );
				break;
			case PEAR_TRANSFORM_SCALE:
				scaleMat = glm::scale( scaleMat, vector );
				break;
		}
		
		localMat = glm::mat4(1.0f);
		localMat = transMat * rotationMat * scaleMat;
		
		for( int i = 0; i < renderables.size(); ++i )
		{
			difference = glm::vec2(	renderables[i]->x - m_Origin.x, renderables[i]->y - m_Origin.y );
			
			glm::mat4 matrix = glm::mat4(1.0f);
			
			matrix = glm::translate( matrix, glm::vec3( difference.x, difference.y, 0.0f ) );
			matrix = localMat * matrix;
			matrix = glm::translate( matrix, glm::vec3(-difference.x,-difference.y, 0.0f ) );
			
			renderables[i]->globalMat = matrix;
		}
	}
	
} }
