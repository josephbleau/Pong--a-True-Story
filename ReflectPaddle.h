#ifndef REFLECTPADDLE_H
#define REFLECTPADDLE_H

#include "Paddle.h"
#include "Event.h"
#include "EventListener.h"
#include "Actor.h"

class Map;

class ReflectPaddle : public Paddle
{
public:
	ReflectPaddle(EventHandler *event_handler, Map *map,
		   float x, float y);
	~ReflectPaddle();

	void Notify(Event *e);
};

#endif