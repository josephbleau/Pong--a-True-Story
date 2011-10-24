#ifndef PLAYERCOLLIDEDWITHACTOR_H
#define PLAYERCOLLIDEDWITHACTOR_H

#include "PlayerEvent.h"
#include "Actor.h"
#include "Player.h"

class ActorCollidedWithActorEvent : public Event
{
protected:
	Actor *a1;
	Actor *a2;

public:
	ActorCollidedWithActorEvent(Actor *a1, Actor *a2);
	~ActorCollidedWithActorEvent();

	double GetActorID();
	Actor *GetActor1();
	Actor *GetActor2();
};

#endif