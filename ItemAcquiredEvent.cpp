#include "ItemAcquiredEvent.h"

ItemAcquiredEvent::ItemAcquiredEvent(std::string name, std::string flavor) : Event(EVT_ITEM_ACQUIRED)
{
	this->name = name;
	this->flavor = flavor;
}

ItemAcquiredEvent::~ItemAcquiredEvent()
{
}

std::string ItemAcquiredEvent::Name()
{
	return this->name; 
}

std::string ItemAcquiredEvent::Flavor()
{
	return this->flavor; 
}