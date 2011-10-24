#include "TickEvent.h"

TickEvent::TickEvent(Uint32 delta) : Event(EVT_TICK)
{
	this->delta = delta;
}

TickEvent::~TickEvent()
{
}

Uint32 TickEvent::Delta()
{
	return this->delta;
}