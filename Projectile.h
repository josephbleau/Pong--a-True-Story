#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Actor.h"
#include "EventListener.h"

class Event;
class EventHandler;
class Map;
class EventListener;

class Projectile : public Actor
{
	Projectile(EventHandler *event_handler, Map *map, 
		       float x, float y, float x_vel, float y_vel,
			   SDL_Surface *sprite);
	~Projectile();

	bool reflected;
	int damage;
public:

	static 
	Projectile *GenerateStandardProjectile(EventHandler *event_handler, 
	                                        Map *map, float x, float y, 
											float x_vel, float y_vel);
										
	void Notify(Event *event);
	int GetDamage();
};

#endif