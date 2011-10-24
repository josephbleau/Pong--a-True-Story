#include "FallingTerrain.h"

#include "EventHandler.h"
#include "Map.h"
#include "Event.h"
#include "ActorCollidedWithActorEvent.h"
#include "TickEvent.h"

FallingTerrain::FallingTerrain(float x, float y, EventHandler *event_handler, Map *map, Uint32 delay) : SpecialTerrain(x, y, event_handler, map)
{
	this->delay_in_ms = delay;
	this->touched = false;
	this->touched_at = 0;
}

FallingTerrain::~FallingTerrain()
{
}

void FallingTerrain::Notify(Event *e)
{
	if(e->ID() == EVT_TICK)
	{
		TickEvent *te = (TickEvent*) e;
		Uint32 delta = te->Delta();

		if(SDL_GetTicks() - touched_at > delay_in_ms){
			if(this->touched)
			{
				if(y < this->map->HeightInPx())
					this->y = float(y + 300.0 * delta/1000.0);
			}
		}
	}

	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR)
	{
		ActorCollidedWithActorEvent* ev = (ActorCollidedWithActorEvent*) e;
		if(ev->GetActor1() == this &&
		   ev->GetActor2()->ID() == ACT_PLAYER)
		{
			if(!touched){
				this->touched = true;
				this->touched_at = SDL_GetTicks();
			}
		}
	}
}

