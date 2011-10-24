#ifndef RENDEREVENT_H
#define RENDEREVENT_H

#include <SDL/SDL.h>
#include "Event.h"

class RenderEvent : public Event
{
	SDL_Surface *screen;

public:
	RenderEvent(SDL_Surface *screen);
	~RenderEvent();

	SDL_Surface * const Screen();
};

#endif