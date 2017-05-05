#ifndef PEAR_UTILITIES_STRING_MANIPULATIONS_H
#define PEAR_UTILITIES_STRING_MANIPULATIONS_H

#include <string>

namespace pear { namespace utils {
	
	enum class FileExtention { 	NONE,
								PNG, JPEG, BMP,
								TTF, TEXTURE };
	
	// returns position of searching word in text
	// if word is not found the returning result is -1
	int findWord( const char* text, const char* word );
	
	std::string getLine( const char* text, unsigned int line_no );
	unsigned int howManyLines( const char* text );
	
	const char* changeFileExtention( const char* filename, const char* new_extention );
	FileExtention getFileExtention( const char* filename );
	
} }

#endif // PEAR_UTILITIES_STRING_MANIPULATIONS_H
