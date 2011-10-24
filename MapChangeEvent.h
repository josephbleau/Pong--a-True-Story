#ifndef MAPCHANGEEVENT_H
#define MAPCHANGEEVENT_H

#include <string>

#include "Event.h"
#include "EventHandler.h"
#include "EventListener.h"

class MapChangeEvent : public Event
{
	std::string filename;

public:
	MapChangeEvent(std::string filename);
	~MapChangeEvent();

	std::string Filename();
};

#endif