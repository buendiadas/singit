#include "Theme.h"

Theme::Theme()
{
}

Theme::Theme(string theme, SDL_Surface *screen)
{
	this->screen = screen;
	this->theme = theme;

	string themepath = "themes/" + theme;
	string backgroundpath = themepath + "/background.jpg";

	SDL_Surface *temp;

	temp = IMG_Load(backgroundpath.c_str());

	this->backgroundsurface = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);
}
