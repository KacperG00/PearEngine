#ifndef PEAR_WINDOW_H
#define PEAR_WINDOW_H

#include <SDL.h>
#include <GL/glew.h>

namespace pear {
	
	class Window
	{
		const char* m_Title;
		int m_Width, m_Height;
		
		SDL_Window* m_Window;
		SDL_GLContext m_Context;
		
	public:
		Window( const char* title, int width, int height );
		~Window();
		void clearScreen();
		void swap();
		void resize();
		
		inline int getWidth() { return m_Width; }
		inline int getHeight() { return m_Height; }
	};
	
}

#endif // PEAR_WINDOW_H
