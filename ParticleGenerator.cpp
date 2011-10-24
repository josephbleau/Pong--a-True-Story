#include "ParticleGenerator.h"
#include "Map.h"
#include "EventHandler.h"
#include "TickEvent.h"
#include "Event.h"

Particle::Particle(float x, float y, float xvel, float yvel, 
	               SDL_Surface *sprite, Map *map, EventHandler *event_handler) 
: Actor(x, y, sprite, map, event_handler)
{
	this->x_velocity = xvel;
	this->y_velocity = yvel;
	this->ethereal = true;
	this->collidable = true;
	this->time_created = SDL_GetTicks();
	this->time_to_live = rand()%2000+2000; /* 2 sec */
}

Particle::~Particle()
{
}

void Particle::StickToFloor(){ this->stick_to_floor = true; }

void Particle::Notify(Event *e)
{
	if(e->ID() == EVT_TICK)
	{
		if(SDL_GetTicks() - this->time_created > this->time_to_live)
			this->map->UnregisterActor(this);

		this->UpdateLocation((TickEvent*)e);

		if(this->falling == false && this->stick_to_floor)
		{
			this->x_velocity = 0;
			this->y_velocity = 0;
		}
	}
}

ParticleGenerator::ParticleGenerator(){}
ParticleGenerator::~ParticleGenerator(){}

void ParticleGenerator::GenerateBloodSplatter(float x, float y, Map *map)
{
	/* generate 20-70 random particles */
	for(unsigned i = 0; i < (unsigned) rand()%50+20; i++)
	{
		float xvel = (float)(rand()%400-200);
		float yvel = (float)(rand()%400-500);
		SDL_Surface *surface = SDL_CreateRGBSurface( SDL_SWSURFACE, 5, 5, 32, 0, 0, 0, 0 );

		/* Create a random surface with 3 possible colors */
		switch( rand() % 3 )
		{
		case 0:
			{
				SDL_FillRect(surface, NULL, 0xff0000);
				break;
			}
		case 1:
			{
				SDL_FillRect(surface, NULL, 0xaa0000);
				break;
			}
		case 2:
			{
				SDL_FillRect(surface, NULL, 0x550000);
				break;
			}
		}

		Particle *p = new Particle(x, y, xvel, yvel,surface, map, map->Handler());
		p->StickToFloor();

		map->RegisterActor(p);
	}
}