#ifndef PEAR_GRAPHICS_RENDERABLE_2D
#define PEAR_GRAPHICS_RENDERABLE_2D

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace pear { namespace graphics {
	
	struct Texture
	{
		unsigned int textureID;
		const char* filename;
		int width, height;
	};
	
	struct Font
	{
		const char* name;
		Texture* texture;
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
		
		struct Color
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
		
		
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
	
	class Renderable2D
	{
	public:
		static unsigned int renderableCount;
		enum class RenderableType { SPRITE, SPRITESHEET } renderableType;
		
		float x, y, z, w, h;
		Texture* texture;
		
		glm::mat4 transMat;
		glm::mat4 rotationMat;
		glm::mat4 scaleMat;
		
		GLuint vbo;
		
	public:
		Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, float depth = 0.0f );
		Renderable2D( RenderableType type, const glm::vec4& pos_and_dim, const char* texture_name, float depth = 0.0f );
		~Renderable2D();
	};
	
} }

#endif // PEAR_GRAPHICS_RENDERABLE_2D
