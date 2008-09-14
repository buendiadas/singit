#ifndef __SONG_H__

#define __SONG_H__

#include <string>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_rotozoom.h>

using namespace std;

class Song
{
        public:

        string title;
        string artist;
        string genre;
        string song;
        string language;
        string cover;
        string background;
        string video;
        int videogap;
        int notesgap;
        int resolution;
        float bpm;
        int gap;
	bool relative;

	string path;

        static string compareby;

	Mix_Music *mixmusic;
	SDL_Surface *backgroundsurface;
	SDL_Surface *coversurface;

	Song();

	Song(string path);

	void parseSongConfFile(string path);
	void play();
	void drawCover(SDL_Surface *screen, int width, int posx, int posy, int alpha);

	static bool compare(Song a, Song b);
};

#endif

