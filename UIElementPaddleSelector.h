#ifndef UIELEMENTPADDLESELECTOR_H
#define UIELEMENTPADDLESELECTOR_H

#include "UIElement.h"

class UIElementPaddleSelector : public UIElement
{
public:
	UIElementPaddleSelector(EventHandler *event_handler, SDL_Surface *screen);
	~UIElementPaddleSelector();

	void Notify(Event *e);
};

#endif