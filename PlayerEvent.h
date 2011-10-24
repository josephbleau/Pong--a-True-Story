#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include "Event.h"
#include "Player.h"

class PlayerEvent : public Event
{
protected:
	Player *who;

public:
	PlayerEvent(Player *who);
	PlayerEvent(EventID id, Player *who);
	~PlayerEvent();

	Player * const Who();
};

#endif