#include "pear_engine.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Utilities/fps_counter.h"
#include "Utilities/fatal_error.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <cstdlib>

using namespace pear;
	
pear_engine::ProgramState pear_engine::program_state = ProgramState::STOPPED;
Window* pear_engine::m_Window = nullptr;

graphics::StaticSpriteRenderer* pear_engine::m_StaticSpriteRenderer = nullptr;
graphics::SpriteRenderer* pear_engine::m_SpriteRenderer = nullptr;

void pear_engine::init()
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
	
	m_StaticSpriteRenderer = new graphics::StaticSpriteRenderer();
	m_SpriteRenderer = new graphics::SpriteRenderer();
	
	graphics::ResourceManager::addTexture( "void.jpg" );
	graphics::ResourceManager::addTexture( "pretty_girl.jpg" );
	graphics::ResourceManager::addTexture( "daredevil.jpg" );
	graphics::ResourceManager::addTexture( "scratches.png" );
	graphics::ResourceManager::addTexture( "sold_out.png" );
	graphics::ResourceManager::addTexture( "SpriteSheets/minotaur.png" );
	
	graphics::ResourceManager::addFont("GloriaHallelujah.ttf");
}

void pear_engine::quit()
{
	if( m_Window != nullptr )
		delete m_Window;
	if( m_StaticSpriteRenderer != nullptr )
		delete m_StaticSpriteRenderer;
	if( m_SpriteRenderer != nullptr )
		delete m_SpriteRenderer;
	
	graphics::ResourceManager::cleanManager();
	
	TTF_Quit();
	SDL_Quit();
}

void pear_engine::run()
{
	using namespace graphics;
	
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4( -1.0f,  1.0f, 2.0f, 2.0f ), glm::vec4( 0x23, 0xa2, 0x52, 0xFF ) ) );
	
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4( -0.9f,  0.9f, 1.8f, 1.8f ), "void.jpg" ) );
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4(  0.1f, -0.1f, 0.8f, 0.8f ), "pretty_girl.jpg" ) );
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4( -0.9f,  0.9f, 0.8f, 0.8f ), "daredevil.jpg", -0.3f ) );
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4(  0.0f,  1.0f, 0.8f, 0.8f ), "sold_out.png" ) );
	m_StaticSpriteRenderer->submit( new Sprite( glm::vec4(  0.0f,  1.0f, 0.8f, 0.8f ), "scratches.png" ) );
	
	m_SpriteRenderer->submit( new SpriteSheet( glm::vec4( -1.0f, 0.0f, 0.4f, 0.7f ), "SpriteSheets/minotaur.png", -0.5f ) );
	m_SpriteRenderer->submit( new SpriteSheet( glm::vec4( -1.0f, 0.0f, 0.4f, 0.7f ), "SpriteSheets/minotaur.png", -0.5f ) );
	m_SpriteRenderer->submit( new Sprite( glm::vec4( -1.0f,-0.25f, 0.5f, 0.5f ), "scratches.png", -0.5f ) );
	m_SpriteRenderer->submit( new Sprite( glm::vec4(  0.0f, 0.0f, 0.5f, 0.5f ), "GloriaHallelujah.ttf", -0.5f ) );
	
	utils::FPSCounter fpsc;
	
	program_state = ProgramState::RUNNING;
	while( program_state == ProgramState::RUNNING )
	{
		//printf( "%f\n", fpsc.fps );
		fpsc.countfps();
		fpsc.limitfps(60);
		
		m_Window->clearScreen();
		m_StaticSpriteRenderer->flush();
		m_SpriteRenderer->flush();
		m_Window->swap();
		
		eventHandling();
		
		SpriteRenderer::WAIT++;
	}
}

void pear_engine::eventHandling()
{
	using namespace graphics;
	
	unsigned int num = 0;
	
	if( Input::isKeyPressed( SDL_SCANCODE_1 ) )
		num = 1;
	if( Input::isKeyPressed( SDL_SCANCODE_2 ) )
		num = 2;
	if( Input::isKeyPressed( SDL_SCANCODE_3 ) )
		num = 3;
	
	if( Input::isKeyPressed( SDL_SCANCODE_W ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.0f, 0.008f, 0.0f ), PEAR_TRANSFORM_TRANSLATE );
	if( Input::isKeyPressed( SDL_SCANCODE_S ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.0f,-0.008f, 0.0f ), PEAR_TRANSFORM_TRANSLATE );
	if( Input::isKeyPressed( SDL_SCANCODE_A ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3(-0.008f, 0.0f, 0.0f ), PEAR_TRANSFORM_TRANSLATE );
	if( Input::isKeyPressed( SDL_SCANCODE_D ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.008f, 0.0f, 0.0f ), PEAR_TRANSFORM_TRANSLATE );
	if( Input::isKeyPressed( SDL_SCANCODE_Q ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.0f, 0.0f,-0.008f ), PEAR_TRANSFORM_ROTATE );
	if( Input::isKeyPressed( SDL_SCANCODE_E ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.0f, 0.0f, 0.008f ), PEAR_TRANSFORM_ROTATE );
	if( Input::isKeyPressed( SDL_SCANCODE_Z ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 1.001f, 1.001f, 1.001f ), PEAR_TRANSFORM_SCALE );
	if( Input::isKeyPressed( SDL_SCANCODE_X ) )
		m_SpriteRenderer->transformMatrix( num, glm::vec3( 0.999f, 0.999f, 0.999f ), PEAR_TRANSFORM_SCALE );
	
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

void pear_engine::initGL()
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
