#ifndef ITEMCOIN_H
#define ITEMCOIN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Item.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "Event.h"

class ItemCoin : public Item
{
public:
	ItemCoin(EventHandler *event_handler, float x, float y, Map *map); 
	~ItemCoin();

	void Notify(Event *e);
};

#endif