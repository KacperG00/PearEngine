#include "PEngine/graphics/sprite.h"

#include "PEngine/app/resource_manager.h"

#include "PEngine/utilities/error.h"

#include <string>

namespace pear { namespace graphics {
	
	unsigned int Sprite::sprite_count = 0;
	
	Sprite::Sprite( const glm::vec4& position_dimensions, const glm::ivec4& color, float depth )
		: Renderable2D( RenderableType::SPRITE, position_dimensions, depth ),
		textureID( 0 ),
		sorted( false )
	{
		col.set( color.x, color.y, color.z, color.w );
		
		sprite_count++;
	}
	
	Sprite::Sprite( const glm::vec4& position_dimensions, const char* texture_name, float depth )
		: Renderable2D( RenderableType::SPRITE, position_dimensions, texture_name, depth ),
		textureID( 0 ),
		sorted( false )
	{
		col.set( 0xFF, 0xFF, 0xFF, 0xFF );
		
		this->uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		
		if( texture == ResourceManager::getTexture( texture_name ) )
		{
			textureID = texture->textureID;
		}
		
		sprite_count++;
	}
	
	Sprite::Sprite( const glm::vec4& position_dimensions, 
					const char* texture_name, 
					const glm::vec4& UV, 
					float depth )
		: Renderable2D( RenderableType::SPRITE, position_dimensions, texture_name, depth ),
		textureID( 0 ),
		sorted( false )
	{
		col.set( 0xFF, 0xFF, 0xFF, 0xFF );
		
		this->uv = UV;
		
		if( texture == ResourceManager::getTexture( texture_name ) )
		{
			textureID = texture->textureID;
		}
		
		sprite_count++;
	}
	
	Sprite::~Sprite()
	{
		sprite_count--;
	}
	
} }
