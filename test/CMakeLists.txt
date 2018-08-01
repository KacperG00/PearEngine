
set(EXECUTABLE_NAME test1)

file( GLOB SOURCES
	"src/main.cpp"
)

add_executable( ${EXECUTABLE_NAME} ${SOURCES} )
target_link_libraries( ${EXECUTABLE_NAME} ${PearEngine_LIBRARY} ${PearEngine_NLIBRARIES} )
