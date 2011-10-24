#include "MenuState.h"

#include "EventListener.h"

#include "TickEvent.h"
#include "RenderEvent.h"
#include "SDLEvent.h"
#include "PlayingState.h"
#include "Game.h"

MenuState::MenuState(Game *parent) : GameState(parent) 
{
	this->background = IMG_Load("data//splash.png");
	this->state = STATE_MENU;
}

MenuState::~MenuState()
{
}

void MenuState::Notify(Event *e)
{
	if(!e)
		return;

	if(e->ID() == EVT_SDL){
		SDLEvent *se = (SDLEvent*) e;
		SDL_Event ev = se->GetSDLEvent();
		if( ev.type == SDL_KEYDOWN )
		{
			/* Some key was pressed. */
			this->parent->EnterNewState( STATE_PLAYING );
		}
	}
}

void MenuState::RenderOverlay(SDL_Surface* screen)
{
	SDL_BlitSurface(this->background, NULL, screen, NULL);
}