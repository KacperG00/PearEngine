cmake_minimum_required(VERSION 3.5.2)
project(PearEngine)

include(FindPkgConfig)

################ LOOKING FOR SDL PACKAGES ########################
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

################ LOOKING FOR OPENGL PACKAGES #####################
find_package(OpenGL)
find_package(GLEW)


set(EngineCoreName ${PROJECT_NAME}Core)
set(PearEngine_LIBRARY ${PearEngine_SOURCE_DIR}/lib/lib${EngineCoreName}.a)
set(PearEngine_NLIBRARIES ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
string(STRIP "${PearEngine_NLIBRARIES}" PearEngine_NLIBRARIES)
set(PearEngine_LIBRARIES "${PearEngine_LIBRARY} ${PearEngine_NLIBRARIES}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PearEngine_SOURCE_DIR}/cmake_modules")
set(LIB_DIR ${PearEngine_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(include)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

add_subdirectory( core )
add_subdirectory( test )

