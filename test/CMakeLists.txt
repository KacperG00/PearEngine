cmake_minimum_required(VERSION 3.5.2)
project(PearEngineTest)

set(CMAKE_BINARY_OUTPUT_DIRECTORY "${PearEngineTest_SOURCE_DIR}")

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

include_directories(${PearEngineTest_SOURCE_DIR}/../include)

file( GLOB SOURCES
	"src/main.cpp"
)

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} "${PearEngineTest_SOURCE_DIR}/../lib/libPearEngine.so" )
