#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL/SDL.h>
#include "EventHandler.h"
#include "EventListener.h"
#include "Event.h"

class Game;
class TickEvent;
class RenderEvent;
class SDLEvent;

enum States { STATE_MENU = 0, STATE_PLAYING, STATE_QUITTING };

class GameState : public EventListener
{
protected:
	SDL_Surface *screen;
	Game *parent;
	States state;

public:
	EventHandler *handler;
	GameState(Game *parent);
	~GameState();

	bool paused;

	EventHandler *StateHandler();
	SDL_Surface *GetOverlay();
	States ID();
	virtual void RenderOverlay(SDL_Surface *screen) = 0;
	virtual void Notify(Event *event) = 0;
};

#endif 
