#ifndef ITEMACQUIREDEVENT_H
#define ITEMACQUIREDEVENT_H

#include <string>

#include "Event.h"
#include "UIElement.h"
#include "UIElementTextBox.h"

class ItemAcquiredEvent : public Event
{
	std::string name;
	std::string flavor;

public:
	ItemAcquiredEvent(std::string name, std::string flavor);
	~ItemAcquiredEvent();

	std::string Name();
	std::string Flavor();
};

#endif