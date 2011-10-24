#include "PlayerCollidedWithActorEvent.h"

PlayerCollidedWithActorEvent::PlayerCollidedWithActorEvent(Player *p, Actor *a) : PlayerEvent(EVT_PLAYER_COLLIDED_WITH_ACTOR, p)
{
	this->a = a;
}

PlayerCollidedWithActorEvent::~PlayerCollidedWithActorEvent()
{

}

double PlayerCollidedWithActorEvent::GetActorID(){ return this->a->ID(); }
Player *PlayerCollidedWithActorEvent::GetPlayer(){ return this->Who(); }
