#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <string>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "EventListener.h"

class EventHandler;
class Event;

class UIElement : public EventListener
{
protected:
	std::string name;

	SDL_Surface *screen;
	SDL_Surface *surf;
	SDL_Rect rect;

public:
	UIElement(EventHandler *event_handler);
	~UIElement();

	void Draw();
	virtual void Notify(Event *e) = 0;
};

#endif