cmake_minimum_required(VERSION 3.5.2)
project(PearEngine)

#option(CrossComp "CrossComp" OFF)
#
#if (CrossComp)
#	SET(CMAKE_SYSTEM_NAME Windows)
#	
#	SET(CMAKE_C_COMPILER i486-mingw32-gcc)
#	SET(CMAKE_CXX_COMPILER i486-mingw32-g++)
#	SET(CMAKE_RC_COMPILER i486-mingw32-windres)
#	
#	SET(CMAKE_FIND_ROOT_PATH /usr/i486-mingw32)
#	
#	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#endif()


set(EngineCoreName ${PROJECT_NAME}Core)
set(PearEngine_LIBRARY ${PearEngine_SOURCE_DIR}/lib/lib${EngineCoreName}.a)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PearEngine_SOURCE_DIR}/cmake_modules")
set(LIB_DIR ${PearEngine_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)


################ LOOKING FOR LIBRARIES #####################
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(PearEngine_NLIBRARIES ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})
string(STRIP "${PearEngine_NLIBRARIES}" PearEngine_NLIBRARIES)
set(PearEngine_LIBRARIES "${PearEngine_LIBRARY} ${PearEngine_NLIBRARIES}")

include_directories("${PearEngine_SOURCE_DIR}/include"
					${SDL2_INCLUDE_DIR}
					${SDL2_IMAGE_INCLUDE_DIR}
					${SDL2_TTF_INCLUDE_DIR})

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

