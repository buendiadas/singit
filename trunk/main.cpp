#include "main.h"

using namespace std;

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

bool addSongs(string path)
{
	DIR * d;
	struct dirent * pdir;
	Song s;
	string str;
	struct stat statd;

	if((d = opendir(path.c_str())) == NULL)
	{
		printf("No se ha podido abrir la carpeta %s\n", path.c_str());
		return false;
	}

	while((pdir = readdir(d)) != NULL)
	{
		str = string(pdir->d_name);
		if(str.compare(".") != 0 && str.compare("..") != 0)
		{
			string tempdir = path + "/" + str;
			stat(tempdir.c_str(), &statd);
			if(statd.st_mode & S_IFDIR)
			{
				s = Song(tempdir);
				if(s.title.compare("") != 0)
				{
					//printf("Canción en: %s\n", tempdir.c_str());
					songs.push_back(s);
				}
			}
		}
	}

	closedir(d);

	songs.sort(Song::compare);

	return true;
}

void run()
{
	double elapsed_time; // Time since last frame
	double actual_time;
	double prev_time = (double) clock();

	// Esta función contendrá el bucle principal

	while(!end)
	{
		actual_time = (double) clock();
		elapsed_time = actual_time - prev_time;

		update(elapsed_time);
		draw(elapsed_time);

		prev_time = actual_time;
	}
}

void manageEvents()
{
	SDL_Event ev;

	while(SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
			case SDL_KEYUP:
				keyboardControl(ev);
				break;
			case SDL_KEYDOWN:
				keyboardControl(ev);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseControl(ev);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseControl(ev);
				break;
			case SDL_MOUSEMOTION:
				mouseControl(ev);
				break;
		}
	}
}

void keyboardControl(SDL_Event ev)
{
	switch(ev.type)
	{
		case SDL_KEYDOWN:
			switch(ev.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					end = true;
					break;
				case SDLK_f:
					fullscreen = !fullscreen;
					break;
				case SDLK_RIGHT:
					selector.selectedsong = (selector.selectedsong + 1) % songs.size();
					break;
				case SDLK_LEFT:
					selector.selectedsong = selector.selectedsong - 1;
					if(selector.selectedsong == -1)
						selector.selectedsong = songs.size()-1;
					break;
				case SDLK_s:
					selector.show();
			}
			break;
		case SDL_KEYUP:
			break;
	}
}

void mouseControl(SDL_Event ev)
{
	switch(ev.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEMOTION:
			break;
	}

}

void update(double t)
{
	manageEvents();

	if(!fullscreen && (screen->flags & SDL_FULLSCREEN))
	{
		screen_flags = screen_flags & ~SDL_FULLSCREEN;
		screen = SDL_SetVideoMode(screen_w, screen_h, screen_d, screen_flags);
	}
	if(fullscreen && !(screen->flags & SDL_FULLSCREEN))
	{
		screen_flags = screen_flags | SDL_FULLSCREEN;
		screen = SDL_SetVideoMode(fs_screen_w, fs_screen_h, screen_d, screen_flags);
	}
}

void draw(double t)
{
	SDL_FillRect(screen, NULL, 0);

	if(selector.showing == true)
	{
		selector.draw(t);
	}

	SDL_Flip(screen);
}


int main(int argc, char *argv[])
{
	printf("Creando juego...\n");

	// Creating subdirs .singit and .singit/songs at $HOME
	// UNIX SPECIFIC
	string homedir = getenv("HOME");
	string singitdir = homedir + "/.singit";
	string songsdir = singitdir + "/songs";
	string commanddir = "mkdir -p " + songsdir;

	system(commanddir.c_str());

	char cwdbuf[255];
	getcwd(cwdbuf, 255);

	currentdir = string(cwdbuf);

	// Default screen properties	
	screen_w = 1024;
	screen_h = 768;
	screen_d = 32;
	screen_flags = 0;
	fs_screen_w = 1280;
	fs_screen_h = 800;

	fullscreen = false;

	SongSelector selector;

	// Initializing SDL
        printf("Iniciando SDL\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
                exit(1);
        }

        atexit(SDL_Quit);

	screen = NULL;

	// Configuring screen
	printf("Configurando pantalla\n");
        screen = SDL_SetVideoMode(screen_w, screen_h, screen_d, screen_flags);
        if(screen == NULL)
        {
                printf("No se puede configurar el modo de video: %s\n", SDL_GetError());
                exit(1);
        }

	// Initializing sound subsystem
	printf("Iniciando subsistema de audio\n");
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1)
	{
		// SDL Audio subsystem could not be started
		printf("Subsistema de audio no iniciado.\n");
	}
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		// SDL_Mixer could not be started
		printf("Mixer no iniciado.\n");
	}

	// Creating song library
	printf("Creando librería de canciones\n");
	addSongs(songsdir);

	selector = SongSelector(songs);

	theme = Theme("default");

	selector.theme = theme;

	printf("\nEjecutando juego...\n");
	run();

        return 0;
}

