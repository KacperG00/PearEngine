#ifndef PEAR_FATALERROR_H
#define PEAR_FATALERROR_H

#include <iostream>

namespace pear {
	
	void fatalError( const char* message )
	{
		std::cout << message << std::endl;
		std::cout << "Type any key to close the program... ";
		char key;
		std::cin >> key;
		
		SDL_Quit();
		exit( 69 );
	}
	
}

#endif // PEAR_FATALERROR_H
