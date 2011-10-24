#include "Item.h"
#include "Map.h"
#include "EventHandler.h"

Item::Item(EventHandler *event_handler, 
	       float x, float y,
	       SDL_Surface *sprite, Map *map) : 
Actor(x,y,sprite,map, event_handler)
{
}

Item::~Item()
{
}

