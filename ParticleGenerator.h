#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "Actor.h"

class Map;
class EventHandler;
class Event;

class Particle : public Actor
{
	Uint32 time_to_live;
	Uint32 time_created;

	bool stick_to_floor;

public:
	Particle(float x, float y, float xvel, float yvel,
		     SDL_Surface *sprite, Map *map,  EventHandler *event_handler);
	~Particle();
	
	void StickToFloor();
	void Notify(Event *e);
};

class ParticleGenerator 
{
protected:

public:
	ParticleGenerator();
	~ParticleGenerator();

	void GenerateBloodSplatter(float x, float y, Map *map);
};

#endif