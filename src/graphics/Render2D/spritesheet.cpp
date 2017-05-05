#include "PEngine/graphics/spritesheet.h"

#include "PEngine/app/resource_manager.h"

#include <iostream>

namespace pear { namespace graphics {
	
	SpriteSheet::SpriteSheet(const glm::vec4& pos_and_dim, const char* texture_name, float depth)
		: Renderable2D( RenderableType::SPRITESHEET, pos_and_dim, texture_name, depth ),
		spriteSheetID( ResourceManager::getRenderable2DCount() ),
		currAnimation( -1 ), currFrame( nullptr )
	{
		addAnimationWithRegDim( 7, 2, 0, 13 );
	}
	
	SpriteSheet::~SpriteSheet()
	{
	}
	
	bool SpriteSheet::ready()
	{
		if( currAnimation == -1 )
		{
			return false;
		}
		
		return true;
	}
	
	glm::vec4* SpriteSheet::getCurrFrame()
	{
		if( currFrame == nullptr )
			nextFrame();
		
		return currFrame;
	}
	
	void SpriteSheet::nextFrame()
	{
		if( currAnimation >= 0 )
			currFrame = animations[currAnimation].getFrame();
		else
			std::cout << "SS_AnimationError! \"currAnimation\" is less than 0!" << std::endl;
	}
	
	void SpriteSheet::startAnimation( unsigned int ani_num )
	{
		currAnimation = ani_num;
	}
	
	void SpriteSheet::addAnimationWithRegDim( int nosh, int nosv, int first_sprite, int last_sprite )
	{
		animations.push_back( SS_Animation( texture->filename.c_str(), nosh, nosv, first_sprite, last_sprite ) );
		startAnimation( 0 );
	}
	
	void SpriteSheet::addAnimationWithSP( const char* animation_name )
	{
		animations.push_back( SS_Animation( texture->filename.c_str(), animation_name ) );
		startAnimation( 0 );
	}
	
} }
