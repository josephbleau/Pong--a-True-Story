#ifndef PLAYERDIEDEVENT_H
#define PLAYERDIEDEVENT_H

#include "Event.h"

class PlayerDiedEvent : public Event
{
public:
	PlayerDiedEvent();
	~PlayerDiedEvent();
};

#endif