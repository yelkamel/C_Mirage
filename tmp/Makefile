SDLFLAGS=-lm `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -lfreetype
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
CFLAGS=-W -Wall -std=c99

all: mirage_sdl mirage_gtk mirage
	./mirage

mirage_sdl: mirage_sdl.c
	gcc -o mirage_sdl mirage_sdl.c $(SDLFLAGS) $(CFLAGS)

mirage_gtk: mirage_gtk.c
	gcc -o mirage_gtk mirage_gtk.c $(GTKFLAGS) $(CFLAGS)

mirage: mirage.c
	gcc -o mirage mirage.c  ${CFLAGS}
	./mirage