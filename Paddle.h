#ifndef PADDLE_H
#define PADDLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "EventListener.h"
#include "Actor.h"

class Map;
class EventHandler;
class Event;

enum PaddleType {PAD_PLATFORM = 0, PAD_REFLECT = 1};

class Paddle :  public Actor
{
protected:
	PaddleType type;

public:
	Paddle(EventHandler *event_handler, Map *map,
		   float x, float y, SDL_Surface *sprite);
	~Paddle();

	virtual void Notify(Event *event) = 0;
	PaddleType Type();
};

#endif