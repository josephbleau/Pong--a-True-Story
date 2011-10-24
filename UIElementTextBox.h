#ifndef UIELEMENTTEXTBOX_H
#define UIELEMENTTEXTBOX_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "EventHandler.h"
#include "UIElement.h"

class PlayingState;
class UIElement;
class Event;

class UIElementTextBox : public UIElement
{
protected:
	TTF_Font *font;
	PlayingState *parent; //for deleting self.

public:
	UIElementTextBox(EventHandler *event_handler, SDL_Surface *screen, 
		             PlayingState *parent, std::string text);
	~UIElementTextBox();

	void Notify(Event *e);
};

#endif