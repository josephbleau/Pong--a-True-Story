#ifndef PLAYERCOLLIDEDWITHACTOR_H
#define PLAYERCOLLIDEDWITHACTOR_H

#include "PlayerEvent.h"
#include "Actor.h"
#include "Player.h"

class PlayerCollidedWithActorEvent : public PlayerEvent
{
protected:
	Actor *a;

public:
	PlayerCollidedWithActorEvent(Player *player, Actor *actor);
	~PlayerCollidedWithActorEvent();

	double GetActorID();
	Player *GetPlayer();
};

#endif