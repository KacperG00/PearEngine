#include "PEngine/utilities/error.h"

#include "PEngine/app/application.h"

#include <iostream>

namespace pear { namespace utils {
	
	void fatalError( const char* format, ... )
	{
		char message[256];
		
		va_list ap;
		va_start( ap, format );
		vsprintf( message, format, ap );
		va_end( ap );
		
		std::cerr << "\nFatalError: \n";
		std::cerr << message << std::endl;
		
		getchar();
		App::quit();
	}
	
	void printError( const char* format, ... )
	{
		char message[256];
		
		va_list ap;
		va_start( ap, format );
		vsprintf( message, format, ap );
		va_end( ap );
		
		std::cerr << "Pear::ERROR: ";
		std::cerr << message << std::endl;
	}
	
} }
