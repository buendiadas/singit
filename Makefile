SMPEGFLAGS=`smpeg-config --libs --cflags`
SDLFLAGS=`sdl-config --libs --cflags`
SDLIMAGEFLAGS=-lSDL_image
SDLMIXERFLAGS=-lSDL_mixer
SDLGFXFLAGS=-lSDL_gfx

ALLFLAGS= $(SDLFLAGS) $(SDLIMAGEFLAGS) $(SMPEGFLAGS) $(SDLMIXERFLAGS) $(SDLGFXFLAGS)

CC=g++

EXECUTABLE=singit

remake: clean singit

singit: Theme.o Song.o SongSelector.o main.o
	$(CC) -o $(EXECUTABLE) Theme.o Song.o SongSelector.o main.o $(ALLFLAGS)

main.o:
	$(CC) -c main.cpp $(ALLFLAGS)

SongSelector.o:
	$(CC) -c SongSelector.cpp SongSelector.h $(SDLFLAGS) $(SDLMIXERFLAGS) $(SDLIMAGEFLAGS) $(SDLGFXFLAGS)

Song.o:
	$(CC) -c Song.cpp Song.h $(SDLFLAGS) $(SDLMIXERFLAGS) $(SDLIMAGEFLAGS) $(SDLGFXFLAGS)

Theme.o:
	$(CC) -c Theme.cpp Theme.h $(SDLFLAGS) $(SDLIMAGEFLAGS)

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
