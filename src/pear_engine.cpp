#include "pear_engine.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "Utilities/timer.h"

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
			initShaders();
			
			m_SpriteRenderer = new pear::SimpleSpriteRenderer();
			
			pear::ResourceManager::addTexture( "void.jpg" );
			pear::ResourceManager::addTexture( "daredevil.jpg" );
			pear::ResourceManager::addTexture( "pretty_girl.jpg" );
		}
	}
}

void Pear_MainProgram::run()
{
	m_SpriteRenderer->submit( new pear::Sprite( glm::vec2( -0.5f, 0.5f ), glm::vec2( 1.0f, 1.0f ), pear::ResourceManager::getTexture( "pretty_girl.jpg" ) ) );
	//m_SpriteRenderer->submit( new pear::Sprite( glm::vec2( -0.5f, 0.5f ), glm::vec2( 1.0f, 1.0f ), glm::vec4( 0xFF, 0xFF, 0xFF, 0xFF ) ) );
	
	pear::Timer timer;
	timer.start();
	
	float velocity = 0.02f;
	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;
	
	program_state = ProgramState::RUNNING;
	while( program_state == ProgramState::RUNNING )
	{
		if( pear::Input::isKeyPressed( SDL_SCANCODE_W ) )
			translation = glm::translate( translation, glm::vec3( 0.0f, velocity, 0.0f ) );
		if( pear::Input::isKeyPressed( SDL_SCANCODE_S ) )
			translation = glm::translate( translation, glm::vec3( 0.0f, -velocity, 0.0f ) );
		if( pear::Input::isKeyPressed( SDL_SCANCODE_A ) )
			translation = glm::translate( translation, glm::vec3( -velocity, 0.0f, 0.0f ) );
		if( pear::Input::isKeyPressed( SDL_SCANCODE_D ) )
			translation = glm::translate( translation, glm::vec3( velocity, 0.0f, 0.0f ) );
		
		if( pear::Input::isKeyPressed( SDL_SCANCODE_Z ) )
			scale = glm::scale( scale, glm::vec3( 1.05f, 1.05f, 1.0f ) );
		if( pear::Input::isKeyPressed( SDL_SCANCODE_X ) )
			scale = glm::scale( scale, glm::vec3( 0.95f, 0.95f, 1.0f ) );
		
		if( pear::Input::isKeyPressed( SDL_SCANCODE_Q ) )
			rotation = glm::rotate( rotation, 0.02f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
		if( pear::Input::isKeyPressed( SDL_SCANCODE_E ) )
			rotation = glm::rotate( rotation, -0.02f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
			
		if( pear::Input::isKeyPressed( SDL_SCANCODE_K ) )
			timer.pause();
		if( pear::Input::isKeyPressed( SDL_SCANCODE_L ) )
			timer.start();
		if( pear::Input::isKeyPressed( SDL_SCANCODE_J ) )
			timer.stop();
		
		trans = translation * scale * rotation;
		
		printf( "%f\n", timer.getTime() );
		
		m_Window->clearScreen();
		
		m_DefaultShader.use();
		m_DefaultShader.setUniformMat4( "transform", trans );
		m_SpriteRenderer->flush();
		m_DefaultShader.unuse();
		
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

void Pear_MainProgram::initShaders()
{
	//m_DefaultShader.compileShaders( "standard_shader" );
	m_DefaultShader.compileShaders( "test_shader" );
	m_DefaultShader.addAttribute( "ourPosition" );
	m_DefaultShader.addAttribute( "ourColor" );
	//m_DefaultShader.addAttribute( "texCoords" );
	//m_DefaultShader.addAttribute( "textureID" );
	m_DefaultShader.linkShaders();
}
