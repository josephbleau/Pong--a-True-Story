#ifndef TICKEVENT_H
#define TICKEVENT_H

#include <SDL/SDL.h>
#include "Event.h"

class TickEvent : public Event
{
	Uint32 delta;
public:
	TickEvent(Uint32 delta);
	~TickEvent();

	Uint32 Delta();
};

#endif