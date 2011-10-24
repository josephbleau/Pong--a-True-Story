#include "UIElement.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "Event.h"

UIElement::UIElement(EventHandler *event_handler) : EventListener(event_handler)
{
	this->name = "";
	this->screen = NULL;
	this->surf = NULL;
}

UIElement::~UIElement()
{
}

void UIElement::Draw()
{
	SDL_BlitSurface(this->surf, NULL, this->screen, &this->rect);
}