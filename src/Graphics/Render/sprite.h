#ifndef PEAR_SPRITE_H
#define PEAR_SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace pear {
	
	struct Vertex
	{
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
		
		float tid;
		
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
	
	class Sprite
	{
		unsigned int m_SpriteID;
		
	public:
		float x, y, w, h;
		Vertex::Color col;
		GLuint textureID;
		
	private:
		GLuint m_VBO;
		
	public:
		Sprite( const glm::vec2& pos, const glm::vec2& dimensions, const glm::vec4& color );
		Sprite( const glm::vec2& pos, const glm::vec2& dimensions, GLuint tID );
		~Sprite();
	};
	
}

#endif // PEAR_SPRITE_H
