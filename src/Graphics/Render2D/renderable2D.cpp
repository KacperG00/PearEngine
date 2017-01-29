#include "renderable2D.h"

#include "../resource_manager.h"

namespace pear { namespace graphics {
	
	unsigned int Renderable2D::renderableCount =  0;
	
	Renderable2D::Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, float depth )
		: x( pos_and_dim.x ), y( pos_and_dim.y ), w( pos_and_dim.z ), h( pos_and_dim.w ),
		transMat( glm::mat4( 1.0f ) ), rotationMat( glm::mat4( 1.0f ) ), scaleMat( glm::mat4( 1.0f ) ),
		vbo( 0 ),
		texture( nullptr ),
		z( depth )
	{
		renderableType = type;
		renderableCount++;
	}
	
	Renderable2D::Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, const char* texture_name, float depth )
		: x( pos_and_dim.x ), y( pos_and_dim.y ), w( pos_and_dim.z ), h( pos_and_dim.w ),
		transMat( glm::mat4( 1.0f ) ), rotationMat( glm::mat4( 1.0f ) ), scaleMat( glm::mat4( 1.0f ) ),
		vbo( 0 ),
		texture( nullptr ),
		z( depth )
	{
		texture = ResourceManager::getTexture( texture_name );
		renderableType = type;
		renderableCount++;
	}
	
	Renderable2D::~Renderable2D()
	{
		if( vbo != 0 )
			glDeleteBuffers( 1, &vbo );
		
		renderableCount--;
	}
	
} }
