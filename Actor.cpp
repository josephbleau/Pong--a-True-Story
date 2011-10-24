#include <cstdio>

#include "Actor.h"
#include "Map.h"
#include "TickEvent.h"
#include "EventHandler.h"
#include "Event.h"

#include "SDL/SDL_rotozoom.h"

Actor::Actor() : EventListener(NULL)
{
	this->x = 0.0;
	this->y = 0.0;
	this->last_x = x;
	this->last_y = y;
	this->sprite = NULL;
	this->falling = false;
	this->map = NULL;
	this->hidden = false;
	this->collidable = true;
	this->sprite_x = 0;
	this->sprite_y = 0;
	this->sprite_w = 0;
	this->sprite_h = 0;
	this->x_velocity = 0;
	this->y_velocity = 0;
	this->grav_on = true;
	this->ethereal = false;
	this->landed_at = SDL_GetTicks();
	this->uid = ACT_NOT_SPECIFIED;
}

Actor::Actor(float x, float y, 
	         SDL_Surface *sprite, Map* map, 
			 EventHandler *event_handler) : 
EventListener(event_handler)
{
	if(!sprite){
		std::cerr << "ERROR LOADING SPRITE\n";
	}
	this->x_velocity = 0;
	this->y_velocity = 0;
	this->x = x;
	this->y = y;
	this->last_x = x;
	this->last_y = y;
	this->sprite = sprite;
	this->sprite_x = 0;
	this->sprite_y = 0;
	this->sprite_w = 0;
	this->landed_at = SDL_GetTicks();
	this->sprite_h = 0;
	this->grav_on = true;
	this->map = map;
	this->falling = true;
	this->hidden = false;
	this->collidable = true;
	this->ethereal = false;
	this->uid = ACT_NOT_SPECIFIED;
	this->land = Mix_LoadWAV("data//snd//land.wav");
}

Actor::~Actor()
{
	if(this->map)
		this->map->UnregisterActor(this);

	if(this->sprite != NULL)
		SDL_FreeSurface(this->sprite);
}

void Actor::BlitTo(SDL_Surface *surface, float x=-1, float y=-1, double scale)
{
	if(this->sprite == NULL ||
	   surface == NULL)
		return;

	SDL_Rect blit_rect;
	
	if(x == -1 && y == -1){
		blit_rect.x = (Sint16) this->x;
		blit_rect.y = (Sint16) this->y;
	} else {
		blit_rect.x = (Sint16) x;
		blit_rect.y = (Sint16) y;
	}

	blit_rect.w = (Uint16) this->sprite->w;
	blit_rect.h = (Uint16) this->sprite->h;


	if(scale != 1){
		SDL_Surface *zoomed = zoomSurface(this->sprite, scale, scale, 0);
		blit_rect.w = (Sint16)(blit_rect.w * scale);
		blit_rect.h = (Sint16)(blit_rect.h * scale);
		SDL_BlitSurface(zoomed, NULL, surface, &blit_rect);
		SDL_FreeSurface(zoomed);
	} else{
		SDL_BlitSurface(this->sprite, NULL, surface, &blit_rect);

	}
}

CollisionAxis Actor::UpdateLocation(TickEvent *e)
{
	Uint32 delta = e->Delta();

	if(delta > 20)
		delta = 1;

	this->last_x = this->x;
	this->last_y = this->y;

	this->x = this->x + float(delta)/1000.0f * this->x_velocity; 

	Actor *collided_with = this->map->IsCollidingWithActor(this);
	if( collided_with ){
			/* Etherial actors can "collide" aka trigger collision events, but 
			   can still be passed through. */
			if(!this->ethereal && !collided_with->ethereal)
				this->x = this->last_x;
	}

	this->y = this->y + float(delta)/1000.0f * this->y_velocity;

	collided_with = this->map->IsCollidingWithActor(this);
	if( collided_with ){
		if(!this->ethereal && !collided_with->ethereal) {
			this->y = this->last_y;

			if(this->y_velocity >= 0)
				this->Landed();
		}
	}

	CollisionAxis collided_along = NO_COLLISION;

	/* Collision code, THIS SERIOUSLY NEEDS TO BE FIXED. Sigh. */
	if( this->collidable ){
		/* more grosness in here! fixfixfix :( */
		collided_along = this->map->IsColliding(this->SX(), this->SY(),
			                                    this->SW(), this->SH());

		if(collided_along != NO_COLLISION){
			if(collided_along == COLLISION_ALONG_X){
				this->x = this->last_x;
				this->x_velocity = 0;
			}
			if(collided_along == COLLISION_ALONG_Y_BOTTOM ){
				this->y = this->last_y;
				this->Landed();
			}
			if(collided_along == COLLISION_ALONG_Y_TOP)
			{
				this->y_velocity = 200;
			}
			if(collided_along == COLLISION_ALONG_ALL)
			{
				this->x = this->last_x;
				this->y = this->last_y;
				this->y_velocity = 0;
				this->x_velocity = 0;
				this->Landed();
			}
		
		} 
	}

	return collided_along;
}

/* (with another actor) */
bool Actor::IsColliding(Actor *a)
{
	float x1 = this->SX();
	float y1 = this->SY();
	float w1 = this->SW();
	float h1 = this->SH();
	float x2 = a->SX();
	float y2 = a->SY();
	float w2 = a->SW();
	float h2 = a->SH();

	if( (y1+h1 < y2 || y1 > y2+h2) ||
		(x1+w1 < x2 ||x1 > x2+w2)){
			return false;
	}

	return true;
}

void Actor::Reflect(bool on_x, bool on_y)
{
	if(on_x)
		this->x_velocity *= -1;
	if(on_y)
		this->y_velocity *= -1;
}

void Actor::Landed()
{
	if(falling == true){
		//Mix_PlayChannel(-1, this->land, 0);
		this->falling = false;
		this->landed_at = SDL_GetTicks();
	}
}

Uint32 Actor::SinceLanded()
{
	return SDL_GetTicks() - this->landed_at;
}

bool Actor::Collidable(){ return this->collidable; }
bool Actor::Hidden(){ return this->hidden; }
float Actor::SX(){ return this->x + this->sprite_x; }
float Actor::SY(){ return this->y + this->sprite_y; }
float Actor::SW(){ return this->W() + this->sprite_w; }
float Actor::SH(){ return this->H() + this->sprite_h; }
float Actor::CX(){ return this->x + this->W()/2; }
float Actor::CY(){ return this->y + this->H()/2; }
float Actor::X(){ return this->x; }
float Actor::Y(){ return this->y; }
float Actor::W(){ if(this->sprite){ return (float) this->sprite->w; } return 0.0; }
float Actor::H(){ if(this->sprite){ return (float) this->sprite->h; } return 0.0; }
double Actor::ID(){ return this->uid; }
bool Actor::GravityOn(){ return this->grav_on; }