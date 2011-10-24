#ifndef ITEM_H
#define ITEM_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Actor.h"

class Item : public Actor
{
public:
	Item(EventHandler *event_handler, float x, float y,
	     SDL_Surface *sprite, Map *map);
	~Item();

	virtual void Notify(Event *event) = 0;
};

#endif