#ifndef FALLWHILEUNDERTERRAIN_H
#define FALLWHILEUNDERTERRAIN_H

#include "SpecialTerrain.h"

class EventHandler;
class Map;
class Event;

class FallWhileUnderTerrain : public SpecialTerrain
{
	Uint32 delay;

public:
	FallWhileUnderTerrain(float x, float y, EventHandler *event_handler, Map *map, Uint32 delay);
	~FallWhileUnderTerrain();

	void Notify(Event *e);
};

#endif