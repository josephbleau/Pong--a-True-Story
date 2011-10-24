#ifndef ITEMPLATFORMPADDLE_H
#define ITEMPLATFORMPADDLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Item.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "Event.h"

class ItemPlatformPaddle : public Item
{
public:
	ItemPlatformPaddle(EventHandler *event_handler, float x, float y, Map *map); 
	~ItemPlatformPaddle();

	void Notify(Event *e);
};

#endif