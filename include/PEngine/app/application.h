#ifndef PEAR_APPLICATION_H
#define PEAR_APPLICATION_H

#include "PEngine/app/window.h"
#include "PEngine/app/input.h"
#include "PEngine/app/resource_manager.h"
#include "PEngine/graphics/render.h"

#define PEAR_APP_RUNNING pear::App::ProgramState::RUNNING
#define PEAR_APP_STOPPED pear::App::ProgramState::STOPPED

namespace pear {
	
	class App
	{
	public:
		static enum class ProgramState { RUNNING, STOPPED } program_state;
		
	private:
		static Window* m_Window;
		
	public:
		static void init();
		static void quit();
		static void eventHandling();
		
		static void clearScreen();
		static void swapScreen();
		
		static void run();
		
		static void setProgramState( ProgramState );
		
		inline static ProgramState& getProgramState() 	{ return program_state; }
		inline static Window* 		getWindow() 		{ return m_Window; }

	private:
		static void initGL();
	};
	
}

#endif // PEAR_APPLICATION_H
