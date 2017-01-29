#include "sprite.h"

#include "../shader.h"
#include "../resource_manager.h"

namespace pear { namespace graphics {
	
	Sprite::Sprite( const glm::vec4& position_dimensions, const glm::vec4& color, float depth )
		: Renderable2D( RenderableType::SPRITE, position_dimensions, depth ),
		textureID( 0 ),
		spriteID( 0 ),
		sorted( false )
	{
		col.r = (int)color.x;
		col.g = (int)color.y;
		col.b = (int)color.z;
		col.a = (int)color.w;
		
		ResourceManager::addSprite( this );
	}
	
	Sprite::Sprite( const glm::vec4& position_dimensions, const char* texture_name, float depth )
		: Renderable2D( RenderableType::SPRITE, position_dimensions, texture_name, depth ),
		spriteID( 0 ),
		sorted( false )
	{
		col.r = col.b = col.a = 0xFF;
		col.g = 0x00;
		
		texture = ResourceManager::getTexture( texture_name );
		textureID = texture->textureID;
		
		ResourceManager::addSprite( this );
	}
	
	Sprite::~Sprite()
	{
	}
	
} }
