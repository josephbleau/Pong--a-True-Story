#ifndef ACTOR_H
#define ACTOR_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "EventListener.h"

class Map;
class TickEvent;
class EventHandler;
class Event;


enum CollisionAxis;

enum ActorType{ ACT_PLAYER = 0, ACT_REF_PAD, 
				ACT_PROJECTILE, ACT_NOT_SPECIFIED,
				ACT_PLAT_PAD_ITEM, ACT_REF_PAD_ITEM, ACT_SPITTER };

class Actor : public EventListener
{
	friend class Map;
protected:
	Map *map;
	SDL_Surface *sprite;
	
	float x, y, x_velocity, y_velocity, last_x, last_y;
	float sprite_x, sprite_y, sprite_w, sprite_h;  /* adjustment values for actual sprite boundaries */

	bool falling;
	bool hidden;
	bool collidable;
	bool ethereal;
	bool grav_on;
	
	Uint32 landed_at; /* time we landed on the ground */

	Mix_Chunk *land;
	ActorType uid;
public:
	Actor();
	Actor(float x, float y, SDL_Surface *sprite, Map *map, EventHandler *event_handler);

	~Actor();

	void BlitTo(SDL_Surface *surface, float x, float y, double scale = 1);

	bool IsColliding(Actor *a);
	CollisionAxis UpdateLocation(TickEvent *e);

	float X(), Y(), W(), H(), CX(), CY();
	float SX(), SY(), SW(), SH();
	double ID();

	bool Collidable();
	bool Hidden();
	bool GravityOn();
	
	void Reflect(bool on_x, bool on_y);

	Uint32 SinceLanded();
	void Landed();
	virtual void Notify(Event *e) = 0;
};

#endif