#include "Paddle.h"

#include "EventHandler.h"
#include <iostream>
Paddle::Paddle(EventHandler *event_handler, Map *map, float x, float y, SDL_Surface *sprite ) :
Actor(x,y, sprite, map, event_handler)
{
	this->collidable = true;
}

Paddle::~Paddle()
{
}

PaddleType Paddle::Type(){ return this->type; }