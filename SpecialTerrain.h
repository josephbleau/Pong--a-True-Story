#ifndef SPECIALTERRAIN_H
#define SPECIALTERRAIN_H

#include "Actor.h"

class EventHandler;
class Event;
class Map;

enum SpecialTerrainType{ TERRAIN_FALLING };

class SpecialTerrain : public Actor
{
	SpecialTerrainType terrain_type;

public:
	SpecialTerrain(float x, float y, EventHandler *event_handler, Map *map);
	~SpecialTerrain();

	void SetSprite(SDL_Surface *surf);
	SpecialTerrainType TerrainType();
	virtual void Notify(Event *e) = 0;
};

#endif