#include "SongSelector.h"

SongSelector::SongSelector()
{
	showing = false;
}

SongSelector::SongSelector(list<Song> songs)
{
	this->songs = songs;
	showing = false;
	selectedsong=0;
}

void SongSelector::show()
{
	showing = true;
}

void SongSelector::draw(double t)
{
	int widthselected = 200;
	int widthnoselected = 100;

	int alphanoselected = 128;

	int separation = 50;

	Song songselected, songleft, songright;
printf("hola5 %d \n", theme.screen->w);
	if(theme.screen->w != theme.backgroundsurface->w && theme.screen->h != theme.backgroundsurface->h)
	{
printf("hola7\n");
		double propw = (double) theme.screen->w / theme.backgroundsurface->w;
		double proph = (double) theme.screen->h / theme.backgroundsurface->h;
		theme.backgroundsurface = zoomSurface(theme.backgroundsurface, propw, proph, 1);
	}
printf("hola6\n");	
	SDL_BlitSurface(theme.backgroundsurface, NULL, theme.screen, NULL);

	list<Song>::iterator it = songs.begin();
	for(int i=0; i < selectedsong; i++)
		it++;

	songselected = *it;

	if(selectedsong == 0)
	{
		songleft = *(--(songs.end()));
		songright = *(++it);
	}
	else if(selectedsong == songs.size() - 1)
	{
		songleft = *(--it);
		songright = *(songs.begin());
	}
	else
	{
		songleft = *(--it);
		it++;
		songright = *(++it);
	}

	int selectedh = songselected.coversurface->h * ((double)widthselected / songselected.coversurface->w);
	int lefth = songleft.coversurface->h * ((double)widthnoselected / songleft.coversurface->w);
	int righth = songright.coversurface->h * ((double)widthnoselected / songright.coversurface->w);

	int selectedx = (theme.screen->w - widthselected) / 2;
	int selectedy = (theme.screen->h - selectedh) / 2;

	int leftx = selectedx - separation - widthnoselected;
	int lefty = (theme.screen->h - lefth) / 2;

	int rightx = selectedx + widthselected + separation;
	int righty = (theme.screen->h - righth) / 2;

	songselected.drawCover(theme.screen, widthselected, selectedx, selectedy, 255);
	songleft.drawCover(theme.screen, widthnoselected, leftx, lefty, alphanoselected);
	songright.drawCover(theme.screen, widthnoselected, rightx, righty, alphanoselected);
}
