#include "PEngine/app/window.h"

#include "PEngine/utilities/error.h"

#include <string>

namespace pear {
	
	Window::Window( const char* title, int width, int height )
		: m_Title( title ), m_Width( width ), m_Height( height ), m_Window( nullptr ), m_Context( 0 )
	{
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		
		m_Window = SDL_CreateWindow( m_Title, 100, 100, m_Width, m_Height,
									SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
		if( m_Window == NULL )
			utils::fatalError( std::string(std::string( "Failed to create window (" ) + m_Title + ")" ).c_str() );
		else
		{
			m_Context = SDL_GL_CreateContext( m_Window );
			if( m_Context == 0 )
				utils::fatalError( std::string(std::string( "Failed to create context for window (" ) + m_Title + ")" ).c_str() );
			else
			{
				glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
			}
		}
	}
	
	Window::~Window()
	{
		SDL_DestroyWindow( m_Window );
		m_Window = nullptr;
		SDL_GL_DeleteContext( m_Context );
	}
	
	void Window::clearScreen()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	
	void Window::swap()
	{
		SDL_GL_SwapWindow( m_Window );
	}
	
	void Window::resize()
	{
		SDL_GetWindowSize( m_Window, &m_Width, &m_Height );
		glViewport( 0, 0, m_Width, m_Height );
	}
	
}
