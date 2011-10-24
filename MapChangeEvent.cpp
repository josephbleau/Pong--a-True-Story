#include "MapChangeEvent.h"

MapChangeEvent::MapChangeEvent(std::string filename) : Event(EVT_MAP_CHANGED)
{
	this->filename = filename;
}

MapChangeEvent::~MapChangeEvent()
{
}

std::string MapChangeEvent::Filename(){ return this->filename; }