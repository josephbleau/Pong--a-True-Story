#include "Enemy.h"
#include "Map.h"
#include "Projectile.h"

/* events-- */
#include "RenderEvent.h"
#include "TickEvent.h"
#include "ActorCollidedWithActorEvent.h"

Enemy::Enemy(float x, float y, Map *map, EventHandler *event_handler) 
: Actor(x, y, IMG_Load("data//chomper.png"), map, event_handler)
{ 
	this->last_shot = SDL_GetTicks();
	this->hp = 4;
}

Enemy::~Enemy()
{
}

void Enemy::Notify(Event *e)
{
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR)
	{
		ActorCollidedWithActorEvent *cwe = (ActorCollidedWithActorEvent*) e;
		if(cwe->GetActor1() == this &&
			cwe->GetActor2()->ID() == ACT_PROJECTILE)
		{
			this->Damage( ((Projectile*)cwe->GetActor2())->GetDamage() );
		}
	}

	if(e->ID() == EVT_TICK)
	{
		if(SDL_GetTicks() - this->last_shot > 1000){
			Projectile *proj = 
				Projectile::GenerateStandardProjectile( this->Handler(),
														this->map,
														this->x-35,
														this->y,
														-200,
														0);

			this->map->RegisterActor(proj);
			this->last_shot = SDL_GetTicks();
		}
	}
	if(e->ID() == EVT_RENDER)
	{
		/* Handled by Map::RenderMap */
	}
}

void Enemy::Damage(int damage)
{
	this->hp -= damage;
	if(hp <= 0)
		this->map->UnregisterActor(this);
}