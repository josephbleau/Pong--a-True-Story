#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "GameState.h"
#include "Event.h"

class EventListener;

class MenuState : public GameState
{
protected:
	SDL_Surface *background;
	
public:
	MenuState(Game *parent);
	~MenuState();

	void Notify(Event *e);
	void RenderOverlay(SDL_Surface *overlay);
};

#endif
