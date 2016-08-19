#include "pear_engine.h"

int main( int argv, const char* args[] )
{
	Pear_MainProgram mainProgram;
	
	mainProgram.init();
	mainProgram.run();
	
	SDL_Quit();
	return 0;
}
