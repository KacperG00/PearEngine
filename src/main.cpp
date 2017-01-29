#include "pear_engine.h"

int main( int argv, const char* args[] )
{
	pear_engine::init();
	pear_engine::run();
	pear_engine::quit();
	
	return 0;
}
