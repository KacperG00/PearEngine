#include "pear_engine.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Utilities/fps_counter.h"
#include "Utilities/fatal_error.h"

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

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
		m_Window = new pear::Window( std::string(std::string("PearEngine | Version: ") + program_version).c_str(), 640, 400 );
		
		GLenum error = glewInit();
		if( error != GLEW_OK )
			pear::fatalError( "Failed to initialize GLEW" );
		else
		{
			pear::Input::init();
			
			m_SpriteRenderer = new pear::SimpleSpriteRenderer();
			
			//pear::ResourceManager::addTexture( "void.jpg" );
			//pear::ResourceManager::addTexture( "daredevil.jpg" );
			//pear::ResourceManager::addTexture( "pretty_girl.jpg" );
			pear::ResourceManager::addTexture( "number0.jpg" );
			pear::ResourceManager::addTexture( "number1.jpg" );
			pear::ResourceManager::addTexture( "number2.jpg" );
			pear::ResourceManager::addTexture( "number3.jpg" );
			pear::ResourceManager::addTexture( "number4.jpg" );
			pear::ResourceManager::addTexture( "number5.jpg" );
			pear::ResourceManager::addTexture( "number6.jpg" );
			pear::ResourceManager::addTexture( "number7.jpg" );
			pear::ResourceManager::addTexture( "number8.jpg" );
			pear::ResourceManager::addTexture( "number9.jpg" );
			pear::ResourceManager::addTexture( "number10.jpg" );
			pear::ResourceManager::addTexture( "number11.jpg" );
			pear::ResourceManager::addTexture( "number12.jpg" );
			pear::ResourceManager::addTexture( "number13.jpg" );
			pear::ResourceManager::addTexture( "number14.jpg" );
			pear::ResourceManager::addTexture( "number15.jpg" );
		}
	}
}

void Pear_MainProgram::run()
{
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec2( -1.0f, 1.0f ), glm::vec2( 2.0f, 2.0f ), glm::vec4( 0x00, 0x00, 0x00, 0xFF ) ) );
	//m_SpriteRenderer->submit( new pear::Sprite( glm::vec2( -1.0f, 1.0f ), glm::vec2( 1.0f, 1.0f ), pear::ResourceManager::getTexture( "void.jpg" ) ) );
	//m_SpriteRenderer->submit( new pear::Sprite( glm::vec2(  0.0f, 1.0f ), glm::vec2( 1.0f, 1.0f ), pear::ResourceManager::getTexture( "pretty_girl.jpg" ) ) );
	//m_SpriteRenderer->submit( new pear::Sprite( glm::vec2(  0.0f, 0.0f ), glm::vec2( 1.0f, 1.0f ), pear::ResourceManager::getTexture( "daredevil.jpg" ) ) );
	
	for( int i = 0; i < 16; i++ )
	{
		m_SpriteRenderer->submit( new pear::Sprite( glm::vec2(  i*(1.0f/8.0f) - 1.0f, i*(1.0f/8.0f) - (1.0f-1.0f/8.0f) ), glm::vec2( 1.0f/8.0f, 1.0f/8.0f ), i+1 ) );
	}
	
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
