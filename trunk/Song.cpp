#ifndef __SONG_CPP__

#define __SONG_CPP___

#include "Song.h"

string Song::compareby = "title";

Song::Song()
{
}

Song::Song(string path)
{
	DIR *dirp;
	struct dirent *direntp;
	bool found = false;
	string str;
	title = "";

	dirp = opendir(path.c_str());

	while((direntp = readdir(dirp)) != NULL && !found)
	{
		str = string(direntp->d_name);

		if(str.size() > 4 && str.substr(str.size() - 4).compare(".txt") == 0)
		{
			found=true;
		}
	}

	if(found)
	{
		this->path = path;
		parseSongConfFile(path + "/" + str);

		// Loading song
		string songpath = path + "/" + song;
		mixmusic = Mix_LoadMUS(songpath.c_str());
		if(mixmusic == NULL)
		{
			printf("No se pudo cargar el archivo %s\n", songpath.c_str());
		}

		// Loading cover surface
		string coverpath = path + "/" + cover;
		SDL_Surface *temp = IMG_Load(coverpath.c_str());
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0);
		coversurface = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		if(coversurface == NULL)
		{
			printf("No se pudo cargar la portada\n");
		}

		// Loading background surface
		string bgpath = path + "/" + background;
		temp = IMG_Load(bgpath.c_str());
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0);
		backgroundsurface = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		if(backgroundsurface == NULL)
		{
			printf("No se pudo cargar el fondo de la canción\n");
		}

	}
}

void Song::parseSongConfFile(string path)
{
	string line;
	ifstream songfile (path.c_str());
	int pos;
	string field;
	string value;
	bool endoffile = false;

	if(songfile.is_open())
	{
		while(!songfile.eof() && !endoffile)
		{
			getline(songfile, line);
			if(line.compare("E") == 0)
			{
				endoffile = true;
			}
			else if(line.find("#",0) == 0 || line.find(":",0) == 0 || line.find("-",0) == 0)
			{
				pos = line.find(":", 0);

				// line is a header
				if(pos>0)
				{
					field = line.substr(0, pos);
					value = line.substr(pos+1, line.length());

					int retpos = value.find("\r");
					if(retpos >= 0)
						value.replace(retpos, 1, "");


					if(field.compare("#TITLE") == 0)
					{
						title = value;
					}
					if(field.compare("#ARTIST") == 0)
					{
						artist = value;
					}
					if(field.compare("#BACKGROUND") == 0)
					{
						background = value;
					}
					if(field.compare("#COVER") == 0)
					{
						cover = value;
					}
					if(field.compare("#MP3") == 0)
					{
						song = value;
					}
					if(field.compare("#BPM") == 0)
					{
						int comapos = value.find(",",0);
						if(comapos > 0)
						{
							value.replace(comapos, 1, ".");
							bpm = atof(value.c_str());
						}
					}
					if(field.compare("#GAP") == 0)
					{
						gap = atoi(value.c_str());
					}
					if(field.compare("#VIDEO") == 0)
					{
						video = value;
					}
					if(field.compare("#VIDEOGAP") == 0)
					{
						videogap = atoi(value.c_str());
					}
					if(field.compare("#NOTESGAP") == 0)
					{
						notesgap = atoi(value.c_str());
					}
					if(field.compare("#RESOLUTION") == 0)
					{
						resolution = atoi(value.c_str());
					}
					if(field.compare("#RELATIVE") == 0)
					{
						relative = (value.compare("yes") == 0)? true : false;
					}
					if(field.compare("#GENRE") == 0)
					{
						genre = value;
					}
					if(field.compare("#LANGUAGE") == 0)
					{
						language = value;
					}
				}
				// line is a song parameter
				else if(pos == 0)
				{
					
				}
			}
		}
	}
}

void Song::play()
{
	if(mixmusic != NULL)
	{
		Mix_PlayMusic(mixmusic, 0);
	}
	else
	{
		printf("No se puede reproducir.\n");
	}
}

bool Song::compare(Song a, Song b)
{
	int c;

	if(compareby.compare("title") == 0)
	{
		c = a.title.compare(b.title);
	}

	return c < 0;
}

void Song::drawCover(SDL_Surface *screen, int width, int posx, int posy, int alpha)
{
	SDL_Rect dest;

	double prop = ((double) width) / coversurface->w;

	SDL_Surface *temp = zoomSurface(coversurface, prop, prop, 1);

	dest.x = posx;
	dest.y = posy;
	dest.w = temp->w;
	dest.h = temp->h;

	SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, alpha); 
	
	SDL_BlitSurface(temp, NULL, screen, &dest);

	SDL_FreeSurface(temp);
}

#endif

