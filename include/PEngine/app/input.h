#ifndef PEAR_INPUT_H
#define PEAR_INPUT_H

#include <SDL2/SDL.h>

namespace pear {
	
#define MAX_KEYBOARD_KEYS 1024
#define MAX_MOUSE_BUTTONS 70
	
	class Input
	{
	private:
		static bool keys[MAX_KEYBOARD_KEYS];
		static bool mouse_buttons[MAX_MOUSE_BUTTONS];
		static int mx, my;
		
	public:
		static SDL_Event evnt;
		
		static void buttonsEventHandling();
		
		static void init();
		static const bool isKeyPressed( SDL_Scancode key );
		static const bool isButtonPressed( unsigned int num );
		
		static void getMousePosition(int& mouse_x, int& mouse_y);
	};
}

#endif // PEAR_INPUT_H
