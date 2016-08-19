DEBUG = -std=c++11 -lSDL2 -lSDL2_image -lGL -lGLEW

PTS = ../src/

ALL_OBJECTS = $(PTS)main.cpp $(MAIN_ITEMS_OBJECTS) $(WINDOW_OBJECTS) $(SHADER_OBJECTS) $(RENDER_OBJECTS) $(RESOURCES_OBJECTS) $(INPUT_OBJECTS) $(UTILS_OBJECTS)

MAIN_ITEMS_OBJECTS = pear_engine.o
MAIN_ITEMS_SRC = $(PTS)pear_engine.cpp

WINDOW_OBJECTS = window.o
WINDOW_SRC = $(PTS)Window/window.cpp

SHADER_OBJECTS = shader.o
SHADER_SRC = $(PTS)Graphics/shader.cpp

RENDER_OBJECTS = simple_sprite_renderer.o sprite.o
RENDER_SRC = $(PTS)Graphics/Render/simple_sprite_renderer.cpp $(PTS)Graphics/Render/sprite.cpp

RESOURCES_OBJECTS = resource_manager.o
RESOURCES_SRC = $(PTS)Graphics/resource_manager.cpp

INPUT_OBJECTS = input.o
INPUT_SRC = $(PTS)Input/input.cpp

UTILS_OBJECTS = timer.o
UTILS_SRC = $(PTS)Utilities/timer.cpp

all: $(ALL_OBJECTS)
	g++ $(ALL_OBJECTS) $(DEBUG) -o executable

pear_engine.o: $(MAIN_ITEMS_SRC)
	g++ $(DEBUG) -c $(MAIN_ITEMS_SRC)

window.o: $(WINDOW_SRC)
	g++ $(DEBUG) -c $(WINDOW_SRC)

shader.o: $(SHADER_SRC)
	g++ $(DEBUG) -c $(SHADER_SRC)

simple_sprite_renderer.o: $(RENDER_SRC)
	g++ $(DEBUG) -c $(RENDER_SRC)
sprite.o: $(RENDER_SRC)
	g++ $(DEBUG) -c $(RENDER_SRC)

resource_manager.o: $(RESOURCES_SRC)
	g++ $(DEBUG) -c $(RESOURCES_SRC)

input.o: $(INPUT_SRC)
	g++ $(DEBUG) -c $(INPUT_SRC)

timer.o: $(UTILS_SRC)
	g++ $(DEBUG) -c $(UTILS_SRC)

clean:
	rm *.o
