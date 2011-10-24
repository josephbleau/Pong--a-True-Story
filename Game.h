#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "GameState.h"

#include "EventHandler.h"
#include "Player.h"
#include "Map.h"

class Game
{
	SDL_Surface *screen;
	SDL_Event sdl_event;

	std::vector<GameState *> state_stack;
	GameState *curstate;
	GameState *prevstate;

public:
	Game(SDL_Surface *screen);
	~Game();

	void Run();

	void EnterNewState(States state);
	void PrevState();

	SDL_Surface *Screen();
	Mix_Chunk *bg;
};

#endif