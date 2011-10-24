#include "PlayerCollidedEvent.h"

PlayerCollidedEvent::PlayerCollidedEvent(Player *who) : PlayerEvent(EVT_PLAYER_COLLIDED, who)
{
}

PlayerCollidedEvent::~PlayerCollidedEvent()
{

}

