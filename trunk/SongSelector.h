#ifndef __SONGSELECTOR_H__

#define __SONGSELECTOR_H__

#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "Song.h"
#include "Theme.h"

class SongSelector
{
	public:

	bool showing;
	list<Song> songs;
	Theme theme;

	int selectedsong;

	SongSelector();
	SongSelector(list<Song> songs);

	void show();
	void draw(double t);
};

#endif

