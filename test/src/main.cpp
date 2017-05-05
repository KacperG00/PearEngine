#include "PEngine/pear_engine.h"

int main(int argv, const char* args[])
{
	pear::App::init();
	
	pear::ResourceManager::addTexture( "void.jpg" );
	pear::ResourceManager::addTexture( "pretty_girl.jpg" );
	pear::ResourceManager::addTexture( "daredevil.jpg" );
	pear::ResourceManager::addTexture( "scratches.png" );
	pear::ResourceManager::addTexture( "sold_out.png" );
	pear::ResourceManager::addTexture( "SpriteSheets/minotaur.png" );
	
	pear::ResourceManager::addFont("SourceCodePro-Regular.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Medium.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Semibold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Bold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Black.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Light.ttf");
	pear::ResourceManager::addFont("SourceCodePro-ExtraLight.ttf");
	
	pear::graphics::SpriteRenderer* sprite_renderer = new pear::graphics::SpriteRenderer;
	
	pear::graphics::Label* label = new pear::graphics::Label( glm::vec2(-1.0f, 1.0f), "SourceCodePro-Bold.ttf", 16 );
	
	
	sprite_renderer->submit(label);
	
	label->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	
	label->setResolution(92);
	
	pear::utils::FPSCounter fpsc;
	
	while( pear::App::getProgramState() == PEAR_APP_RUNNING )
	{
		fpsc.countfps();
		
		label->setText("fps: %.3f", fpsc.fps);
		
		pear::App::clearScreen();
		sprite_renderer->flush();
		pear::App::swapScreen();
		
		pear::App::eventHandling();
	}
	
	delete sprite_renderer;
	
	pear::App::quit();
	
	return 0;
}
