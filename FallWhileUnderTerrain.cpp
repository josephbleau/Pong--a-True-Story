#include "FallWhileUnderTerrain.h"

#include "EventHandler.h"
#include "Map.h"
#include "Event.h"
#include "PlayerMovedEvent.h"
#include "ActorCollidedWithActorEvent.h"
#include "TickEvent.h"

FallWhileUnderTerrain::FallWhileUnderTerrain(float x, float y, EventHandler *event_handler, Map *map, Uint32 delay) : SpecialTerrain(x, y, event_handler, map)
{
	this->ethereal = true;
	this->collidable = true;
	this->delay = delay;
	this->falling = false;
}

FallWhileUnderTerrain::~FallWhileUnderTerrain()
{
}

void FallWhileUnderTerrain::Notify(Event *e)
{
	if(e->ID() == EVT_TICK)
	{
		TickEvent *te = (TickEvent*) e;
		Uint32 delta = te->Delta();

		if( y < this->map->HeightInPx() && falling )
		{
			this->y += float(400 * delta/1000.0);
		}
		
	}
	if(e->ID() == EVT_PLAYER_MOVED)
	{
		PlayerMovedEvent *pme = (PlayerMovedEvent*) e;
		if(pme->Y() > this->Y() && pme->X() > this->X() && pme->X() < this->X() + this->W()){
			this->falling = true;
		}
	}
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR)
	{
		ActorCollidedWithActorEvent *acwa = (ActorCollidedWithActorEvent*) e;
		if(acwa->GetActor1() == this &&
			acwa->GetActor2()->ID() == ACT_PLAYER)
		{
			((Player*)acwa->GetActor2())->Damage(10);
		}
	}
}

