LINK_OPENGL = -lGL -lGLEW
LINK_FREETYPE2 = -I/usr/local/include/freetype2 -lfreetype

all:
	gcc $(LINK_OPENGL) $(LINK_FREETYPE2) ../texture-font.c ../texture-atlas.c ../vector.c ../distance-field.c ../edtaa3func.c ../platform.c ../text-buffer.c ../utf8-utils.c ../vertex-attribute.c ../vertex-buffer.c -c && ar rsc ../../libfreetype-gl.a distance-field.o edtaa3func.o platform.o text-buffer.o texture-atlas.o texture-font.o utf8-utils.o vector.o vertex-attribute.o vertex-buffer.o && make clean

clean:
	rm *.o
