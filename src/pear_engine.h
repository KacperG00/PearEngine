#ifndef PEAR_ENGINE_H
#define PEAR_ENGINE_H

#include "Window/window.h"
#include "Input/input.h"
#include "Graphics/resource_manager.h"
#include "Graphics/shader.h"

#include "Graphics/Render/simple_sprite_renderer.h"

#include <glm/glm.hpp>
#include <string>

const std::string program_version = "0.1";

class Pear_MainProgram
{
	enum class ProgramState { RUNNING, STOPPED } program_state;
	pear::Window *m_Window;
	
	pear::Shader m_DefaultShader;
	
	pear::SimpleSpriteRenderer* m_SpriteRenderer;
	
	glm::mat4 trans;
	
	unsigned int _ms;
	
public:
	Pear_MainProgram();
	~Pear_MainProgram();
	
	void init();
	void run();

private:
	void eventHandling();
	void initShaders();
};

namespace pear {
	
	void fatalError( const char* message );
	
}

#endif // PEAR_ENGINE_H
