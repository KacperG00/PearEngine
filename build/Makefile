DEBUG = -std=c++11 -lSDL2 -lSDL2_image -lGL -lGLEW

PTS = ../src/

ALL_OBJECTS = $(PTS)main.cpp $(MAIN_ITEMS_OBJECTS) $(WINDOW_OBJECTS) $(SHADER_OBJECTS) $(RENDER_OBJECTS) $(RESOURCES_OBJECTS) $(INPUT_OBJECTS) $(UTILS_OBJECTS)

RENDER_OBJECTS = static_sprite_renderer.o sprite.o
RENDER_SRC = $(PTS)Graphics/Render/static_sprite_renderer.cpp $(PTS)Graphics/Render/sprite.cpp

MAIN_ITEMS_OBJECTS = pear_engine.o
WINDOW_OBJECTS = window.o
SHADER_OBJECTS = shader.o
RESOURCES_OBJECTS = resource_manager.o
INPUT_OBJECTS = input.o
UTILS_OBJECTS = timer.o fps_counter.o fatal_error.o

all: $(ALL_OBJECTS)
	g++ $(ALL_OBJECTS) $(DEBUG) -o executable


# MAIN_ITEMS_OBJECTS
pear_engine.o: $(PTS)pear_engine.cpp
	g++ $(DEBUG) -c $(PTS)pear_engine.cpp


# WINDOW_OBJECTS
window.o: $(PTS)Window/window.cpp
	g++ $(DEBUG) -c $(PTS)Window/window.cpp


# SHADER_OBJECTS
shader.o: $(PTS)Graphics/shader.cpp
	g++ $(DEBUG) -c $(PTS)Graphics/shader.cpp


# RENDER_OBJECTS
static_sprite_renderer.o: $(RENDER_SRC)
	g++ $(DEBUG) -c $(RENDER_SRC)
sprite.o: $(RENDER_SRC)
	g++ $(DEBUG) -c $(RENDER_SRC)


# RESOURCES_OBJECTS
resource_manager.o: $(PTS)Graphics/resource_manager.cpp
	g++ $(DEBUG) -c $(PTS)Graphics/resource_manager.cpp


# INPUT_OBJECTS
input.o: $(PTS)Input/input.cpp
	g++ $(DEBUG) -c $(PTS)Input/input.cpp


# UTILS_OBJECTS
timer.o: $(PTS)Utilities/timer.cpp
	g++ $(DEBUG) -c $(PTS)Utilities/timer.cpp
fps_counter.o: $(PTS)Utilities/fps_counter.cpp
	g++ $(DEBUG) -c $(PTS)Utilities/fps_counter.cpp
fatal_error.o: $(PTS)Utilities/fatal_error.cpp
	g++ $(DEBUG) -c $(PTS)Utilities/fatal_error.cpp

clean:
	rm *.o
