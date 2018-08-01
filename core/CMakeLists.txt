
set(	GRAPHICS_SRC_FILES
	"src/graphics/*.cpp"
	"src/graphics/Render2D/*.cpp"
	"src/graphics/Render3D/*.cpp"
)
set(	APP_SRC_FILES
	"src/app/*.cpp"
)
set(	UTILITIES_SRC_FILES
	"src/utilities/*.cpp"
)

file(GLOB SOURCES
	${GRAPHICS_SRC_FILES}
	${APP_SRC_FILES}
	${UTILITIES_SRC_FILES}
)

add_library( ${EngineCoreName} STATIC ${SOURCES} )
target_link_libraries(${EngineCoreName} ${PearEngine_NLIBRARIES})
