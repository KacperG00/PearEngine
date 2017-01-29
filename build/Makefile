LINK = -std=c++11
LINK_ALL = -std=c++11 $(LINK_SDL2) $(LINK_OPENGL) $(LINK_FREETYPE2)
LINK_SDL2 = -lSDL2 -lSDL2_image -lSDL2_ttf $(LINK_FREETYPE2)
LINK_OPENGL = -lGL -lGLEW
LINK_FREETYPE2 = -I/usr/local/include/freetype2 -lfreetype

PTS = ../src/

ALL_OBJECTS = $(PTS)main.cpp $(MAIN_ITEMS_OBJECTS) $(WINDOW_OBJECTS) $(SHADER_OBJECTS) $(RENDER_OBJECTS) $(RESOURCES_OBJECTS) $(INPUT_OBJECTS) $(UTILS_OBJECTS)

RENDER_OBJECTS = $(RENDER2D_OBJECTS) $(RENDER3D_OBJECTS)

RENDER2D_OBJECTS = renderable2D.o sprite_renderer.o static_sprite_renderer.o sprite.o spritesheet.o animation.o
RENDER2D_FOLDER = $(PTS)Graphics/Render2D/
RENDER2D_SRC = $(RENDER2D_FOLDER)renderable2D.cpp $(RENDER2D_FOLDER)sprite_renderer.cpp $(RENDER2D_FOLDER)static_sprite_renderer.cpp $(RENDER2D_FOLDER)sprite.cpp $(RENDER2D_FOLDER)spritesheet.cpp $(RENDER2D_FOLDER)animation.cpp

RENDER3D_OBJECTS = renderer3D.o
RENDER3D_FOLDER = $(PTS)Graphics/Render3D/
RENDER3D_SRC = $(RENDER3D_FOLDER)renderer3D.cpp

MAIN_ITEMS_OBJECTS = pear_engine.o
WINDOW_OBJECTS = window.o
SHADER_OBJECTS = shader.o
RESOURCES_OBJECTS = resource_manager.o
INPUT_OBJECTS = input.o
UTILS_OBJECTS = timer.o fps_counter.o fatal_error.o string_manipulations.o

all: $(ALL_OBJECTS)
	g++ $(ALL_OBJECTS) $(LINK_ALL) -o executable


# MAIN_ITEMS_OBJECTS
pear_engine.o: $(PTS)pear_engine.cpp
	g++ $(LINK_ALL) -c $(PTS)pear_engine.cpp


# WINDOW_OBJECTS
window.o: $(PTS)Window/window.cpp
	g++ $(LINK) $(LINK_SDL2) $(LINK_OPENGL) -c $(PTS)Window/window.cpp


# SHADER_OBJECTS
shader.o: $(PTS)Graphics/shader.cpp
	g++ $(LINK_ALL) -c $(PTS)Graphics/shader.cpp


# RENDER_OBJECTS
# RENDER 2D
renderable2D.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)
sprite_renderer.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)
static_sprite_renderer.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)
sprite.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)
spritesheet.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)
animation.o: $(RENDER2D_SRC)
	g++ $(LINK_ALL) -c $(RENDER2D_SRC)

# RENDER 3D
renderer3D.o: $(RENDER3D_SRC)
	g++ $(LINK_ALL) -c $(RENDER3D_SRC)


# RESOURCES_OBJECTS
resource_manager.o: $(PTS)Graphics/resource_manager.cpp
	g++ $(LINK_ALL) -c $(PTS)Graphics/resource_manager.cpp


# INPUT_OBJECTS
input.o: $(PTS)Input/input.cpp
	g++ $(LINK) $(LINK_SDL2) -c $(PTS)Input/input.cpp


# UTILS_OBJECTS
timer.o: $(PTS)Utilities/timer.cpp
	g++ $(LINK_ALL) -c $(PTS)Utilities/timer.cpp
fps_counter.o: $(PTS)Utilities/fps_counter.cpp
	g++ $(LINK_ALL) -c $(PTS)Utilities/fps_counter.cpp
fatal_error.o: $(PTS)Utilities/fatal_error.cpp
	g++ $(LINK_ALL) -c $(PTS)Utilities/fatal_error.cpp
string_manipulations.o: $(PTS)Utilities/string_manipulations.cpp
	g++ $(LINK) -c $(PTS)Utilities/string_manipulations.cpp

clean:
	rm *.o
