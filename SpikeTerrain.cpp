#include "SpikeTerrain.h"

#include "EventHandler.h"
#include "Map.h"
#include "Event.h"
#include "ActorCollidedWithActorEvent.h"
#include "TickEvent.h"

SpikeTerrain::SpikeTerrain(float x, float y, EventHandler *event_handler, Map *map) : SpecialTerrain(x, y, event_handler, map)
{
	this->ethereal = true;
	this->collidable = true;
}

SpikeTerrain::~SpikeTerrain()
{
}

void SpikeTerrain::Notify(Event *e)
{

	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR)
	{
		ActorCollidedWithActorEvent* ev = (ActorCollidedWithActorEvent*) e;
		if(ev->GetActor1() == this &&
		   ev->GetActor2()->ID() == ACT_PLAYER)
		{
			((Player*)ev->GetActor2())->Damage(2);
		}
	}
}

