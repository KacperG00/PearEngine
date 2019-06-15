
set(EXECUTABLE_NAME greenscreen_test)

add_executable( ${EXECUTABLE_NAME} "greenscreen_test.cpp" )
target_link_libraries( ${EXECUTABLE_NAME} ${PearEngine_LIBRARY} ${PearEngine_NLIBRARIES} )
