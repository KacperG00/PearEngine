#include "sprite.h"

#include "../resource_manager.h"

#include <iostream>
#include <string>
#include <cstddef>

namespace pear {
	
	unsigned int Sprite::_spriteCount = 0;
	
	Sprite::Sprite( const glm::vec4& position_dimensions, const glm::vec4& color, float depth )
		: x(position_dimensions.x), y(position_dimensions.y), z( depth ), w(position_dimensions.z), h(position_dimensions.w), textureID( 0 ),
		spriteID( _spriteCount + 1 ),
		sorted( false )
	{
		_spriteCount++;
		
		col.r = (int)color.x;
		col.g = (int)color.y;
		col.b = (int)color.z;
		col.a = (int)color.w;
	}
	
	Sprite::Sprite( const glm::vec4& position_dimensions, GLuint tID, float depth )
		: x(position_dimensions.x), y(position_dimensions.y), z( depth ), w(position_dimensions.z), h(position_dimensions.w),
		textureID( tID ),
		spriteID( _spriteCount + 1 ),
		sorted( false )
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
