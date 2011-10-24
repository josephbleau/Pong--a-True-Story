#include "Event.h"

Event::Event()
{
	this->id = EVT_GENERIC;
}

Event::Event(EventID id)
{
	this->id = id;
}

Event::~Event()
{
}

EventID Event::ID()
{
	return this->id;
}