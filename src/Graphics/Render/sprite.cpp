#include "sprite.h"

#include "../resource_manager.h"

#include <iostream>
#include <string>
#include <cstddef>

namespace pear {
	
	unsigned int Sprite::_spriteCount = 0;
	
	Sprite::Sprite( const glm::vec2& pos, const glm::vec2& dimensions, const glm::vec4& color )
		: x(pos.x), y(pos.y), w(dimensions.x), h(dimensions.y), textureID( 0 ),
		spriteID( _spriteCount + 1 )
	{
		_spriteCount++;
		
		col.r = (int)color.x;
		col.g = (int)color.y;
		col.b = (int)color.z;
		col.a = (int)color.w;
	}
	
	Sprite::Sprite( const glm::vec2& pos, const glm::vec2& dimensions, GLuint tID )
		: x(pos.x), y(pos.y), w(dimensions.x), h(dimensions.y),
		textureID( tID ),
		spriteID( _spriteCount + 1 )
	{
		_spriteCount++;
		
		col.r = col.b = col.a = 0xFF;
		col.g = 0x00;
	}
	
	Sprite::~Sprite()
	{
		_spriteCount--;
	}
	
}
