#ifndef PEAR_ENGINE_H
#define PEAR_ENGINE_H

#include "Window/window.h"
#include "Input/input.h"

#include "resource_manager.h"

#include "Graphics/Render2D/static_sprite_renderer.h"
#include "Graphics/Render2D/sprite_renderer.h"

#include <string>

class pear_engine
{
	static enum class ProgramState { RUNNING, STOPPED, MINIMALIZED } program_state;
	static pear::Window *m_Window;
	
	static pear::graphics::StaticSpriteRenderer* m_StaticSpriteRenderer;
	static pear::graphics::SpriteRenderer* m_SpriteRenderer;
	
public:
	static void init();
	static void quit();
	static void run();

private:
	static void eventHandling();
	static void initGL();
};

#endif // PEAR_ENGINE_H
