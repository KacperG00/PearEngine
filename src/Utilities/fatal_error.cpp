#include "fatal_error.h"

#include <SDL2/SDL.h>
#include <iostream>

namespace pear { namespace utils {
	
	void fatalError( const char* message )
	{
		std::cout << message << std::endl;
		std::cout << "Type any key to close the program... ";
		char key;
		std::cin >> key;
		
		SDL_Quit();
		exit( 69 );
	}
	
} }
