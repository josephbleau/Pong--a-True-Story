#include "EventListener.h"
#include "EventHandler.h"

EventListener::EventListener()
{
}

EventListener::EventListener(EventHandler *event_handler)
{
	if(event_handler)
		this->handler = event_handler;
	else
		this->handler = new EventHandler();

	this->handler->RegisterListener(this);
}

EventListener::~EventListener()
{
	/* unregister ourselves with the handler */
	if(this->handler)
		handler->UnregisterListener(this);
}

EventHandler * EventListener::Handler()
{
	return this->handler;
}