#ifndef PEAR_GRAPHICS_RENDERABLE_2D
#define PEAR_GRAPHICS_RENDERABLE_2D

#include "PEngine/graphics/transformation_types.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

namespace pear { namespace graphics {
	
#ifndef PEAR_GRAPHICS_COLOR_STRUCT
#define PEAR_GRAPHICS_COLOR_STRUCT

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		
		Color& set( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
			
			return *this;
		}
	};
	
#endif // PEAR_GRAPHICS_COLOR_STRUCT
	
	struct Texture
	{
		unsigned int textureID;
		std::string filename;
		int width, height;
	};
	
#ifndef PEAR_GRAPHICS_VERTEXDATA
#define PEAR_GRAPHICS_VERTEXDATA

	struct Vertex
	{
		float tid;
		
		struct Position
		{
			float x;
			float y;
			float z;
		} position;
		
		struct UV
		{
			float s;
			float t;
		} uv;
		
		Color color;
		
		void setPosition( float X, float Y, float Z )
		{
			this->position.x = X;
			this->position.y = Y;
			this->position.z = Z;
		}
		void setUV( float S, float T )
		{
			this->uv.s = S;
			this->uv.t = T;
		}
		void setColor( unsigned char R, unsigned char G, unsigned char B, unsigned char A )
		{
			this->color.r = R;
			this->color.g = G;
			this->color.b = B;
			this->color.a = A;
		}
	};
	
#endif // PEAR_GRAPHICS_VERTEXDATA
	
	class Renderer2D;
	
	class Renderable2D
	{
	public:
		enum class RenderableType { SPRITE, SPRITESHEET, GROUP, LABEL } renderableType;
		unsigned long int id;
		
		Renderer2D *renderer;
		
		float x, y, z, w, h;
		Texture* texture;
		glm::vec4 uv;
		
		glm::mat4 globalMat;
		glm::mat4 localMat;
		
		glm::mat4 transMat;
		glm::mat4 rotationMat;
		glm::mat4 scaleMat;
		
		GLuint vbo;
		
	public:
		Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, float depth = 0.0f );
		Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, const char* texture_name, float depth = 0.0f );
		~Renderable2D();
		void setUV( const glm::vec4& uv );
		void transform( PearTransformationType type, const glm::vec3& vector, float angle = 1.0f );
	};
	
} }

#endif // PEAR_GRAPHICS_RENDERABLE_2D
