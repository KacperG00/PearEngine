#include "PEngine/graphics/renderable2D.h"

#include "PEngine/app/resource_manager.h"

namespace pear { namespace graphics {
	
	Renderable2D::Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, float depth )
		: id( 0 ), renderer( NULL ),
		x( pos_and_dim.x ), y( pos_and_dim.y ), w( pos_and_dim.z ), h( pos_and_dim.w ),
		uv( glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) ),
		globalMat( glm::mat4( 1.0f ) ), localMat( glm::mat4( 1.0f ) ),
		transMat( glm::mat4( 1.0f ) ), rotationMat( glm::mat4( 1.0f ) ), scaleMat( glm::mat4( 1.0f ) ),
		vbo( 0 ), texture( nullptr ),
		z( depth )
	{
		renderableType = type;
		ResourceManager::addRenderable2D( this );
	}
	
	Renderable2D::Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, const char* texture_name, float depth )
		: id( 0 ), renderer( NULL ),
		x( pos_and_dim.x ), y( pos_and_dim.y ), w( pos_and_dim.z ), h( pos_and_dim.w ),
		uv( glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) ),
		globalMat( glm::mat4( 1.0f ) ), localMat( glm::mat4( 1.0f ) ),
		transMat( glm::mat4( 1.0f ) ), rotationMat( glm::mat4( 1.0f ) ), scaleMat( glm::mat4( 1.0f ) ),
		vbo( 0 ), texture( nullptr ),
		z( depth )
	{
		texture = ResourceManager::getTexture( texture_name );
		renderableType = type;
		ResourceManager::addRenderable2D( this );
	}
	
	Renderable2D::~Renderable2D()
	{
		if( vbo != 0 )
			glDeleteBuffers( 1, &vbo );
	}
	
	void Renderable2D::setUV( const glm::vec4& uv )
	{
		this->uv = uv;
	}
	
	void Renderable2D::transform( PearTransformationType type, const glm::vec3& vector, float angle )
	{
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
		
		localMat = transMat * rotationMat * scaleMat;
	}
	
} }
