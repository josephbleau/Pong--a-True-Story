#include "GameState.h"

#include "TickEvent.h"
#include "RenderEvent.h"
#include "SDLEvent.h"
#include "Game.h"

GameState::GameState(Game *parent) : EventListener(NULL)
{
	this->parent = parent;
	this->paused = false;
	this->screen = this->parent->Screen();
}

GameState::~GameState()
{

}

States GameState::ID(){ return this->state;}