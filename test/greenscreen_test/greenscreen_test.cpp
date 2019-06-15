#include "PEngine/pear_engine.h"

int main(int argv, const char* args[])
{
	pear::App::init();
	
	pear::ResourceManager::addShader("standard_sprite_shader");
	
	pear::ResourceManager::addTexture( "gs.jpg" );
	
	pear::ResourceManager::addFont("SourceCodePro-Regular.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Medium.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Semibold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Bold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Black.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Light.ttf");
	pear::ResourceManager::addFont("SourceCodePro-ExtraLight.ttf");
	
	pear::graphics::SpriteRenderer* sprite_renderer = new pear::graphics::SpriteRenderer;
	sprite_renderer->bindShader("standard_sprite_shader");
	
	pear::graphics::Sprite* me_gs = new pear::graphics::Sprite(glm::vec4(-1.0f, 1.0f, 2.0f, 2.0f), "gs.jpg");
	
	sprite_renderer->submit(me_gs);
	
	while( pear::App::getProgramState() == PEAR_APP_RUNNING )
	{
		pear::App::clearScreen();
		sprite_renderer->flush();
		pear::App::swapScreen();
		
		pear::App::eventHandling();
	}
	
	delete sprite_renderer;
	
	pear::App::quit();
	
	return 0;
}
