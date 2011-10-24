#ifndef FALLINGTERRAIN_H
#define FALLINGTERRAIN_H

#include "SpecialTerrain.h"

class EventHandler;
class Map;
class Event;

class FallingTerrain : public SpecialTerrain
{
	bool touched;
	Uint32 touched_at;
	Uint32 delay_in_ms;

public:
	FallingTerrain(float x, float y, EventHandler *event_handler, Map *map, Uint32 delay);
	~FallingTerrain();

	void Notify(Event *e);
};

#endif