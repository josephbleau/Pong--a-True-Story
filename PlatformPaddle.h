#ifndef PLATFORMPADDLE_H
#define PLATFORMPADDLE_H

#include "Paddle.h"
#include "Event.h"
#include "EventListener.h"
#include "Actor.h"

class Map;

class PlatformPaddle : public Paddle
{
public:
	PlatformPaddle(EventHandler *event_handler, Map *map,
		   float x, float y);
	~PlatformPaddle();

	void Notify(Event *e);
};

#endif