#include <SDL/SDL_mixer.h>

#include "Game.h"
#include "conf.h"

SDL_Surface *init_SDL();

int main(int argc, char *argv[])
{
	argv; argc; /*stfu compiler! */

	SDL_Surface *screen = init_SDL();
	if(screen == NULL)
		return 1;

	Game game(screen);
	game.Run();
	
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

SDL_Surface *init_SDL()
{
	SDL_Surface *screen = NULL;
	int error = 0;

	error = SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if(error == -1)
		return NULL;

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0){
		std::cerr << "Unable to initialize audio: " << Mix_GetError() << std::endl;
		return NULL;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		                      SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL)
		return NULL;

	return screen;
}