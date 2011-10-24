#include "RenderEvent.h"

RenderEvent::RenderEvent(SDL_Surface *screen) : Event(EVT_RENDER)
{
	this->screen = screen;
}

RenderEvent::~RenderEvent()
{

}

SDL_Surface * const RenderEvent::Screen()
{
	return screen;
}