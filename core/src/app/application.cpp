#include "PEngine/app/application.h"

#include "PEngine/utilities/fps_counter.h"
#include "PEngine/utilities/error.h"
#include "PEngine/graphics/group.h"
#include "PEngine/graphics/label.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdlib>

namespace pear {
	
	App::ProgramState App::program_state = ProgramState::STOPPED;
	Window* App::m_Window = nullptr;

	void App::init()
	{
		// SDL initialization
		if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
			utils::fatalError( "Failed to initialize SDL!" );
		
		// SDL_image and SDL_ttf
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
			utils::fatalError( "Failed to initialize SDL_images!" );
		if( TTF_Init() < 0 )
			utils::fatalError( "Failed to initialize SDL_ttf!" );
		
		m_Window = new Window( "PearEngine", 640, 400 );
		
		// OpenGL initialization
		initGL();
		
		Input::init();
		
		program_state = ProgramState::RUNNING;
	}

	void App::quit()
	{
		if( m_Window != nullptr )
			delete m_Window;
		
		ResourceManager::cleanManager();
		
		TTF_Quit();
		SDL_Quit();
	}
	
	void App::eventHandling()
	{
		using namespace graphics;
		
		while( SDL_PollEvent( &Input::evnt ) != 0 )
		{
			switch( Input::evnt.type )
			{
				case SDL_QUIT:
				{
					program_state = ProgramState::STOPPED;
				} break;
				case SDL_WINDOWEVENT:
				{
					switch( Input::evnt.window.event )
					{
						case SDL_WINDOWEVENT_RESIZED:
						{
							m_Window->resize();
						} break;
					}
				} break;
			}
			
			Input::buttonsEventHandling();
		}
	}
	
	void App::clearScreen()
	{
		m_Window->clearScreen();
	}
	
	void App::swapScreen()
	{
		m_Window->swap();
	}
	
	void App::setProgramState( ProgramState ps )
	{
		program_state = ps;
	}

	void App::initGL()
	{
		GLenum error = glewInit();
		if( error != GLEW_OK )
			utils::fatalError( "Failed to initialize GLEW" );
		else
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
}
	
}
