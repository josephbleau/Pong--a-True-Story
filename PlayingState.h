#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "GameState.h"
#include "Map.h"

#include "Player.h"
#include "Enemy.h"

class Event;
class EventListener;
class UIElement;

class PlayingState : public GameState
{
protected:
	Map *map;
	Map *last_map;

	Player *player;
	SDL_Surface *mapnamesurf;
	std::vector<UIElement*> ui_elements;

public: 
	PlayingState(Game *parent);
	~PlayingState();

	void Notify(Event *e);

	void RenderOverlay(SDL_Surface *overlay);

	void AddUIElement(UIElement *element);
	void RemoveUIElement(UIElement *element);
};

#endif