#ifndef PEAR_STRING_CONSTANTS_H
#define PEAR_STRING_CONSTANTS_H

#include <string>

namespace pear { 
	
	namespace paths_from_src {
		
		const std::string RESOURCES = "../Resources/";
		const std::string TEXTURES = RESOURCES + "Textures/";
		const std::string FONTS = RESOURCES + "Fonts/";
		
		const std::string GRAPHICS = "Graphics/";
		const std::string SHADERS = GRAPHICS + "Shaders/";
		const std::string RENDER = GRAPHICS + "Render/";
		
	}
	
	namespace paths_from_build {
		
		const std::string FROM_BUILD_TO_SRC = "../src/";
		
		const std::string RESOURCES = FROM_BUILD_TO_SRC + paths_from_src::RESOURCES;
		const std::string TEXTURES = FROM_BUILD_TO_SRC + paths_from_src::TEXTURES;
		const std::string FONTS = FROM_BUILD_TO_SRC + paths_from_src::FONTS;
		
		const std::string GRAPHICS = FROM_BUILD_TO_SRC + paths_from_src::GRAPHICS;
		const std::string SHADERS = FROM_BUILD_TO_SRC + paths_from_src::SHADERS;
		const std::string RENDER = FROM_BUILD_TO_SRC + paths_from_src::RENDER;
		
	}
	
}

#endif // PEAR_STRING_CONSTANTS_H
