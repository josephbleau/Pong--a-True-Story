#ifndef SPIKETERRAIN_H
#define SPIKETERRAIN_H

#include "SpecialTerrain.h"

class EventHandler;
class Map;
class Event;

class SpikeTerrain : public SpecialTerrain
{
public:
	SpikeTerrain(float x, float y, EventHandler *event_handler, Map *map);
	~SpikeTerrain();

	void Notify(Event *e);
};

#endif