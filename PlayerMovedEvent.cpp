#include "PlayerMovedEvent.h"

PlayerMovedEvent::PlayerMovedEvent(Player *who) : 
PlayerEvent(EVT_PLAYER_MOVED, who)
{
}

PlayerMovedEvent::~PlayerMovedEvent()
{
}

float PlayerMovedEvent::X()
{
	return this->Who()->X();
}

float PlayerMovedEvent::Y()
{
	return this->Who()->Y();
}