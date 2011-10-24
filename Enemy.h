#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "EventListener.h"
#include "EventHandler.h"
#include "Event.h"

class Enemy : public Actor
{
	Uint32 last_shot;
	int hp;

public:
	Enemy(float x, float y, Map *map, EventHandler *event_handler);
	~Enemy();

	void Damage(int damage);

	void Notify(Event *e);
};

#endif