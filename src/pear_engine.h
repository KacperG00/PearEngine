#ifndef PEAR_ENGINE_H
#define PEAR_ENGINE_H

#include "Window/window.h"
#include "Input/input.h"

#include "Graphics/resource_manager.h"

#include "Graphics/Render/static_sprite_renderer.h"

#include <string>

const std::string program_version = "0.1";

class Pear_MainProgram
{
	enum class ProgramState { RUNNING, STOPPED } program_state;
	pear::Window *m_Window;
	
	pear::StaticSpriteRenderer* m_SpriteRenderer;
	
public:
	Pear_MainProgram();
	~Pear_MainProgram();
	
	void init();
	void run();

private:
	void eventHandling();
	void initGL();
};

#endif // PEAR_ENGINE_H
