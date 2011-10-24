#include "EventHandler.h"
#include <iostream>
#include <algorithm>
EventHandler::EventHandler()
{
	this->clear = false;
}

EventHandler::~EventHandler()
{
}

void EventHandler::DispatchEvent(Event *e)
{
	for(unsigned i = 0; i < this->listeners.size(); i++)
	{
		if(this->listeners[i]){
			EventListener *listener = this->listeners[i];
			listener->Notify(e);
		}

		if(this->clear){
			this->clear = false;
			break;
		}
	}
}

void EventHandler::ClearEvents()
{
	this->clear = true;
}

void EventHandler::RegisterListener(EventListener *listener)
{
	if(listener == NULL){
		std::cerr << "Tried pushing NULL listener, sorry no thanks\n";
		return;
	}

	this->listeners.push_back(listener);
}

void EventHandler::UnregisterAll()
{
	this->listeners.clear();
}

void EventHandler::UnregisterListener(EventListener *listener)
{
	if(listener)
	{
		auto it = std::find(this->listeners.begin(), this->listeners.end(), listener);

		if(it != this->listeners.end() ){
			this->listeners.erase(it);
		}
	}
}