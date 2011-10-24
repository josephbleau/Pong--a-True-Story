#include "PlayerEvent.h"

PlayerEvent::PlayerEvent(Player *who) : Event(EVT_PLAYER)
{
	this->who = who;	
}

PlayerEvent::PlayerEvent(EventID id, Player *who) : Event(id)
{
	this->who = who;
}

PlayerEvent::~PlayerEvent()
{
}

Player * const PlayerEvent::Who()
{
	return this->who;
}