CC=clang
CFLAGS=`sdl2-config --cflags --libs` -lSDL2_ttf -W 

all:
	$(CC) -o main $(CFLAGS) *.c

clean:
	rm *.o
