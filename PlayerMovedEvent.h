#ifndef PLAYERMOVEDEVENT_H
#define PLAYERMOVEDEVENT_H

#include "Player.h"
#include "PlayerEvent.h"

class PlayerMovedEvent : public PlayerEvent
{
	float x,y;

public:
	PlayerMovedEvent(Player *who);
	~PlayerMovedEvent();

	float X();
	float Y();
};

#endif