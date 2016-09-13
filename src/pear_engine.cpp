#include "pear_engine.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Utilities/fps_counter.h"
#include "Utilities/fatal_error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cstdlib>

Pear_MainProgram::Pear_MainProgram()
	: program_state( ProgramState::STOPPED ),
	m_Window( nullptr ),
	m_SpriteRenderer( nullptr )
{
}

Pear_MainProgram::~Pear_MainProgram()
{
	if( m_Window != nullptr )
		delete m_Window;
	if( m_SpriteRenderer != nullptr )
		delete m_SpriteRenderer;
	
	pear::ResourceManager::cleanManager();
}

void Pear_MainProgram::init()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		pear::fatalError( "Failed to initialize SDL!" );
	else
	{
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
			pear::fatalError( "Failed to initialize SDL_images!" );
		
		m_Window = new pear::Window( std::string(std::string("PearEngine | Version: ") + program_version).c_str(), 640, 400 );
		
		initGL();
		
		pear::Input::init();
		
		m_SpriteRenderer = new pear::StaticSpriteRenderer();
		
		pear::ResourceManager::addTexture( "void.jpg" );
		pear::ResourceManager::addTexture( "pretty_girl.jpg" );
		pear::ResourceManager::addTexture( "daredevil.jpg" );
		pear::ResourceManager::addTexture( "scratches.png" );
		pear::ResourceManager::addTexture( "sold_out.png" );
	}
}

void Pear_MainProgram::run()
{
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec4( -0.9f,  0.9f, 1.8f, 1.8f ), pear::ResourceManager::getTexture( "void.jpg" ) ) );
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec4(  0.1f, -0.1f, 0.8f, 0.8f ), pear::ResourceManager::getTexture( "pretty_girl.jpg" ) ) );
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec4( -0.9f,  0.9f, 0.8f, 0.8f ), pear::ResourceManager::getTexture( "daredevil.jpg" ), -0.3f ) );
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec4(  0.0f,  1.0f, 0.8f, 0.8f ), pear::ResourceManager::getTexture( "sold_out.png" ) ) );
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec4(  0.0f,  1.0f, 0.8f, 0.8f ), pear::ResourceManager::getTexture( "scratches.png" ) ) );
	
	pear::FPSCounter fpsc;
	
	program_state = ProgramState::RUNNING;
	while( program_state == ProgramState::RUNNING )
	{
		//printf( "%f\n", fpsc.fps );
		fpsc.countfps();
		
		m_Window->clearScreen();
		m_SpriteRenderer->flush();
		m_Window->swap();
		
		eventHandling();
	}
}

void Pear_MainProgram::eventHandling()
{
	using namespace pear;
	
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

void Pear_MainProgram::initGL()
{
	GLenum error = glewInit();
	if( error != GLEW_OK )
		pear::fatalError( "Failed to initialize GLEW" );
	else
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
