#ifndef SDLEVENT_H
#define SDLEVENT_H

#include <SDL/SDL.h>
#include "Event.h"

class SDLEvent : public Event
{
	SDL_Event sdl_event;

public:
	SDLEvent(SDL_Event sdl_event);
	~SDLEvent();

	SDL_Event GetSDLEvent();
};

#endif