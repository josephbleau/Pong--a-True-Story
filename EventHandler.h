#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>

#include "Event.h"
#include "EventListener.h"

class EventHandler 
{
	std::vector<EventListener*> listeners;
	bool clear;

public:
	EventHandler();
	~EventHandler();

	void DispatchEvent(Event *e);
	void ClearEvents();

	void RegisterListener(EventListener *listener);
	void UnregisterListener(EventListener *listener);
	void UnregisterAll();
};

#endif