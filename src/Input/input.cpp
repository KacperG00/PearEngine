#include "input.h"

#include <iostream>

namespace pear {
	
	SDL_Event Input::evnt;
	bool Input::keys[MAX_KEYBOARD_KEYS];
	bool Input::mouse_buttons[MAX_MOUSE_BUTTONS];
	int Input::mx;
	int Input::my;
	
	void Input::buttonsEventHandling()
	{
		if( evnt.type == SDL_KEYDOWN || evnt.type == SDL_KEYUP )
			if( evnt.key.keysym.scancode > MAX_KEYBOARD_KEYS )
				return;
		
		switch( evnt.type )
		{
			case SDL_KEYDOWN:
				keys[evnt.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				keys[evnt.key.keysym.scancode] = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[evnt.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mouse_buttons[evnt.button.button] = false;
				break;
			case SDL_MOUSEMOTION:
				mx = evnt.motion.x;
				my = evnt.motion.y;
				break;
		}
	}
	
	void Input::init()
	{
		for( int i = 0; i < MAX_KEYBOARD_KEYS; i++ )
			keys[i] = false;
		for( int i = 0; i < MAX_MOUSE_BUTTONS; i++ )
			mouse_buttons[i] = false;
	}
	
	const bool Input::isKeyPressed( SDL_Scancode sc )
	{
		return keys[sc];
	}
	
	const bool Input::isButtonPressed( unsigned int num )
	{
		return mouse_buttons[num];
	}
}
