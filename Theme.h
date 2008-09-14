#ifndef __THEME_H__

#define __THEME_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Theme
{
	public:

	string theme;

	SDL_Surface *screen;
	SDL_Surface *backgroundsurface;

	string themepath;
	string backgroundpath;

	Theme();
	Theme(string theme, SDL_Surface *screen);
};

#endif

