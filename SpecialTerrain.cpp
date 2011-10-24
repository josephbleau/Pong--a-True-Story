#include "SpecialTerrain.h"

#include "EventHandler.h"
#include "Event.h"
#include "Map.h"

SpecialTerrain::SpecialTerrain(float x, float y, EventHandler *event_handler, Map *map) : 
Actor(x, y, NULL, map, event_handler)
{
}

SpecialTerrain::~SpecialTerrain()
{
}

void SpecialTerrain::SetSprite(SDL_Surface *surf)
{
	if(surf != NULL)
		this->sprite = surf;
}

SpecialTerrainType SpecialTerrain::TerrainType(){ return this->terrain_type; }