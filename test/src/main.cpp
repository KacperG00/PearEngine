#include "PEngine/pear_engine.h"

#include <unistd.h>

int main(int argv, const char* args[])
{
	pear::App::init();
	
	
	//pear::ResourceManager::addTexture( "somepicture.jpg" );
	
	pear::ResourceManager::addFont("SourceCodePro-Regular.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Medium.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Semibold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Bold.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Black.ttf");
	pear::ResourceManager::addFont("SourceCodePro-Light.ttf");
	pear::ResourceManager::addFont("SourceCodePro-ExtraLight.ttf");
	
	pear::graphics::SpriteRenderer* sprite_renderer = new pear::graphics::SpriteRenderer;
	
	pear::graphics::Label* label_fps = new pear::graphics::Label( glm::vec2(-1.0f,  0.9f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label_mouse = new pear::graphics::Label( glm::vec2(-1.0f,  0.7f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label1 = new pear::graphics::Label( glm::vec2(-1.0f, -0.5f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label2 = new pear::graphics::Label( glm::vec2(-1.0f, -0.3f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label3 = new pear::graphics::Label( glm::vec2(-1.0f, -0.1f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label4 = new pear::graphics::Label( glm::vec2(-1.0f,  0.1f), "SourceCodePro-Bold.ttf", 16 );
	pear::graphics::Label* label5 = new pear::graphics::Label( glm::vec2(-1.0f,  0.3f), "SourceCodePro-Bold.ttf", 16 );
	
	//pear::graphics::Sprite* sprite = new pear::graphics::Sprite( glm::vec4(-1.0f, 1.0f, 2.0f, 2.0f), "void.jpg" );
	
	//sprite_renderer->submit(sprite);
	
	//for(unsigned int i = 0; i < 100; ++i)
	//{
	//	for(unsigned int j = 0; j < 100; ++j)
	//	{
	//		sprite = new pear::graphics::Sprite(glm::vec4((float)i*0.02f-1.0f, 1.0f-(float)j*0.02f, 0.02f, 0.02f), "scratches.png");
	//		sprite_renderer->submit(sprite);
	//	}
	//}
	
	sprite_renderer->submit(label_fps);
	sprite_renderer->submit(label_mouse);
	sprite_renderer->submit(label1);
	sprite_renderer->submit(label2);
	sprite_renderer->submit(label3);
	sprite_renderer->submit(label4);
	sprite_renderer->submit(label5);
	
	label_fps->setResolution(32);
	label_fps->setTextColor( 0xCF, 0x30, 0x40, 0xFF );
	label_mouse->setResolution(32);
	label_mouse->setTextColor( 0xCF, 0x30, 0x40, 0xFF );
	label1->setResolution(8);
	label1->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	label2->setResolution(16);
	label2->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	label3->setResolution(32);
	label3->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	label4->setResolution(64);
	label4->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	label5->setResolution(128);
	label5->setTextColor( 0xEF, 0xAb, 0x60, 0xFF );
	
	pear::utils::FPSCounter fpsc;
	
	int mx, my;
	
	while( pear::App::getProgramState() == PEAR_APP_RUNNING )
	{
		fpsc.countfps();
		
		label_fps->setText("fps: %.3f", fpsc.fps);
		pear::Input::getMousePosition(mx, my);
		label_mouse->setText("%d, %d", mx, my);
		label1->setText("Font size 8");
		label2->setText("Font size 16");
		label3->setText("Font size 32");
		label4->setText("Font size 64");
		label5->setText("Font size 128");
		
		pear::App::clearScreen();
		sprite_renderer->flush();
		pear::App::swapScreen();
		
		pear::App::eventHandling();
	}
	
	delete sprite_renderer;
	
	pear::App::quit();
	
	return 0;
}
