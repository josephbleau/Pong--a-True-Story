#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Event.h"
class EventHandler;

class EventListener
{
	EventHandler *handler;

public:
	EventListener();
	EventListener(EventHandler *event_handler);
	~EventListener();

	virtual EventHandler * Handler();
	virtual void Notify(Event *e) = 0;
};

#endif