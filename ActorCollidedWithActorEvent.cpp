#include "ActorCollidedWithActorEvent.h"

ActorCollidedWithActorEvent::ActorCollidedWithActorEvent(Actor *a1, Actor *a2) : 
Event(EVT_ACTOR_COLLIDED_WITH_ACTOR)
{
	this->a1 = a1;
	this->a2 = a2;
}

ActorCollidedWithActorEvent::~ActorCollidedWithActorEvent()
{

}

Actor *ActorCollidedWithActorEvent::GetActor2(){ return this->a1; }
Actor *ActorCollidedWithActorEvent::GetActor1(){ return this->a2; }
