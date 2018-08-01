#ifndef PEAR_STRING_CONSTANTS_H
#define PEAR_STRING_CONSTANTS_H

#include <string>

namespace pear { 
	
	namespace paths_from_bin{
		
		const std::string RESOURCES = "../resources/";
		const std::string TEXTURES = RESOURCES + "Textures/";
		const std::string FONTS = RESOURCES + "Fonts/";
		const std::string SHADERS = RESOURCES + "Shaders/";

	}

	namespace paths_from_src {
		
		const std::string RESOURCES = "../resources/";
		const std::string TEXTURES = RESOURCES + "Textures/";
		const std::string FONTS = RESOURCES + "Fonts/";
		
		const std::string GRAPHICS = "graphics/";
		const std::string SHADERS = GRAPHICS + "Shaders/";
		const std::string RENDER2D = GRAPHICS + "Render2D/";
		const std::string RENDER3D = GRAPHICS + "Render3D/";
		
	}
	
	namespace paths_from_build {
		
		const std::string FROM_BUILD_TO_SRC = "../src/";
		
		const std::string RESOURCES = FROM_BUILD_TO_SRC + paths_from_src::RESOURCES;
		const std::string TEXTURES = FROM_BUILD_TO_SRC + paths_from_src::TEXTURES;
		const std::string FONTS = FROM_BUILD_TO_SRC + paths_from_src::FONTS;
		
		const std::string GRAPHICS = FROM_BUILD_TO_SRC + paths_from_src::GRAPHICS;
		const std::string SHADERS = FROM_BUILD_TO_SRC + paths_from_src::SHADERS;
		const std::string RENDER2D = FROM_BUILD_TO_SRC + paths_from_src::RENDER2D;
		const std::string RENDER3D = FROM_BUILD_TO_SRC + paths_from_src::RENDER3D;
		
	}
	
}

#endif // PEAR_STRING_CONSTANTS_H
