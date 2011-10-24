#include "Game.h"

/* events -- */
#include "SDLEvent.h"
#include "RenderEvent.h"
#include "TickEvent.h"

/* states -- */
#include "PlayingState.h"
#include "MenuState.h"

#include "conf.h"

Game::Game(SDL_Surface *screen)
{
	this->screen = screen;

	MenuState *s = new MenuState(this);
	this->state_stack.push_back(s);
	this->curstate = s;
	this->bg = Mix_LoadWAV("data//snd//bg.mp3");
}

Game::~Game()
{
}

void Game::Run()
{
	RenderEvent render_event(this->screen);
	Uint32 lastframe = SDL_GetTicks();

	Mix_PlayChannel(-1, this->bg, 0);

	while(this->curstate->ID() != STATE_QUITTING)
	{
		TickEvent tick_event(SDL_GetTicks() - lastframe);
		lastframe = SDL_GetTicks();

		while(SDL_PollEvent(&this->sdl_event))
		{
			if(this->sdl_event.type == SDL_QUIT)
				goto quit;
			else{
				SDLEvent sdl_event(this->sdl_event);
				this->curstate->Handler()->DispatchEvent(&sdl_event);
			}
		}
	
		if(this->curstate->paused)
			continue;

		this->curstate->Handler()->DispatchEvent(&tick_event);
		this->curstate->Handler()->DispatchEvent(&render_event);

		this->curstate->RenderOverlay(this->screen);
		SDL_Flip(this->screen);

		SDL_Rect clear_rect;
		clear_rect.x = 0;
		clear_rect.y = 0;
		clear_rect.w = (Uint16) this->screen->w;
		clear_rect.h = (Uint16) this->screen->h;
		
		SDL_FillRect(this->screen, &clear_rect, 0x0);
	}

quit:
	return;
}

void Game::EnterNewState(States state)
{
	if(state == STATE_PLAYING)
	{
		this->prevstate = this->curstate;
		PlayingState *ps = new PlayingState(this);
		this->state_stack.push_back( ps);
		this->curstate = this->state_stack[ this->state_stack.size()-1 ];
	}
}

void Game::PrevState()
{
	GameState *t = this->curstate;
	this->curstate = this->prevstate;
	this->prevstate = t;
}

SDL_Surface *Game::Screen() { return this->screen; }