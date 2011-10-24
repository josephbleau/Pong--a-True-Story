#include "Projectile.h"
#include "Event.h"
#include "EventHandler.h"
#include "Map.h"

#include "TickEvent.h"
#include "ActorCollidedWithActorEvent.h"

Projectile::Projectile(EventHandler *event_handler, Map *map, 
	                   float x, float y, float x_vel, float y_vel, 
					   SDL_Surface *sprite) :
Actor(x,y,sprite,map,event_handler)
{
	this->x_velocity = x_vel;
	this->y_velocity = y_vel;
	this->grav_on = false;
	this->collidable = true;
	this->ethereal = true;
	this->uid = ACT_PROJECTILE;
	this->reflected = false;
	this->damage = 2; /* todo, fix*/
	this->sprite_h = -10;
}

Projectile::~Projectile()
{
}

Projectile *Projectile::GenerateStandardProjectile(EventHandler *event_handler, Map *map, 
	                                               float x, float y, float x_vel, float y_vel)
{
	SDL_Surface *surf = IMG_Load("data//projectile.png");
	return new Projectile(event_handler, map, x, y, x_vel, y_vel, surf);
}

void Projectile::Notify(Event *e)
{
	if(e->ID() == EVT_TICK)
	{
		CollisionAxis result = this->UpdateLocation((TickEvent*) e);
		if(result != NO_COLLISION)
			this->map->UnregisterActor(this);
		
	}
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR)
	{
		ActorCollidedWithActorEvent *ae = (ActorCollidedWithActorEvent*) e;
		if( ae->GetActor1()->ID() == ACT_REF_PAD &&
			ae->GetActor2() == this )
		{
			if(!this->reflected){
				ae->GetActor2()->Reflect(true, true); /* Ping pong! o.O */
				this->reflected = true;
			}
		}
		if(	ae->GetActor2() == this  )
		{
			if(ae->GetActor1()->ID() == ACT_REF_PAD){
				this->Reflect(true,false);
			} else{
				this->map->UnregisterActor(this);
			}
		}
	}
}

int Projectile::GetDamage(){ return this->damage; }