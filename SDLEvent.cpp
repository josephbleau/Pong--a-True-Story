#include "SDLEvent.h"

SDLEvent::SDLEvent(SDL_Event sdl_event) : Event(EVT_SDL)
{
	this->sdl_event = sdl_event;
}

SDLEvent::~SDLEvent()
{
}

SDL_Event SDLEvent::GetSDLEvent()
{
	return this->sdl_event;
}