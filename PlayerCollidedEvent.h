#ifndef PLAYERCOLLIDEDEVENT_H
#define PLAYERCOLLIDEDEVENT_H

#include "PlayerEvent.h"

class PlayerCollidedEvent : public PlayerEvent
{

public:
	PlayerCollidedEvent(Player *who);
	~PlayerCollidedEvent();
};

#endif