#ifndef __SINGIT_H__

#define __SINGIT_H__

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <smpeg.h>
#include <ctime>
#include <string>
#include <fstream>

#include <stdlib.h>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "Song.h"
#include "SongSelector.h"
#include "Theme.h"

using namespace std;

class SingIt
{
	private:
	SDL_Surface *screen;
	bool fullscreen;
	int screen_w;
	int screen_h;
	int fs_screen_w;
	int fs_screen_h;
	int screen_d;
	int screen_flags;

	bool end;

	string singitdir;
	string songsdir;
	string currentdir;
	list<Song> songs;

	Theme theme;
	SongSelector selector;

	void manageEvents();
        void keyboardControl(SDL_Event ev);
        void mouseControl(SDL_Event ev);

        void draw(double t);
        void update(double t);

	bool addSongs(string path);

	public:
	void run();
	SingIt();
};

#endif

