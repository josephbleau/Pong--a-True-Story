#ifndef ITEMREFLECTPADDLE_H
#define ITEMREFLECTPADDLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Item.h"


class ItemReflectPaddle : public Item
{
public:
	ItemReflectPaddle(EventHandler *event_handler, float x, float y, Map *map); 
	~ItemReflectPaddle();

	void Notify(Event *e);
};

#endif