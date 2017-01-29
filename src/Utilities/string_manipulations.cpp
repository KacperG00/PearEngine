#include "string_manipulations.h"

#include <string>

namespace pear { namespace utils {
	
	int findWord( const char* text, const char* word )
	{
		std::string spring = text;
		std::string theWord = word;
		
		for( int i = 0; i < spring.size(); i++ )
		{
			if( spring[i] == theWord[0] )
			{
				for( int j = 0; j < theWord.size() || theWord[j] == ' '; j++ )
				{
					if( spring[i+j] != theWord[j] )
						break;
					
					if( j == theWord.size()-1 || theWord[j+1]==' ' )
						return i;
				}
			}
		}
		
		return -1;
	}
	
	const char* changeFileExtention( const char* filename, const char* new_extention )
	{
		std::string text = filename;
		std::string newName = "";
		
		for( int i = text.size() - 1; i >= 0; i-- )
		{
			if( text[i] == '.' )
			{
				for( int j = 0; j <= i; j++ )
				{
					newName += text[j];
				}
				newName += new_extention;
				break;
			}
		}
		
		return newName.c_str();
	}
	
	FileExtention getFileExtention( const char* filename )
	{
		FileExtention extention = FileExtention::NONE;
		std::string wholeName = filename;
		std::string extentionString = "";
		
		for( int i = wholeName.size() - 1; i >= 0; i-- )
		{
			if( wholeName[i] == '.' )
			{
				for( int j = i+1; j < wholeName.size(); j++ )
					extentionString += wholeName[j];
				
				break;
			}
		}
		
		if( extentionString == "jpg" || extentionString == "jpeg" )
			extention = FileExtention::JPEG;
		else if( extentionString == "png" )
			extention = FileExtention::PNG;
		else if( extentionString == "bmp" )
			extention = FileExtention::BMP;
		else
			extention = FileExtention::NONE;
		
		return extention;
	}
	
} }
