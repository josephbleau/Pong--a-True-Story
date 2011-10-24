#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>

#include <SDL/SDL_mixer.h>

#include "Actor.h"
#include "EventListener.h"

class Map;
class PlatformPaddle;
class Paddle;

class Player : public Actor
{
protected:
	std::vector<Paddle*> paddles;
	std::map<std::string, bool> usable_paddles;

	float spawn_x, spawn_y;

	int hp;
	Uint32 last_hurt;
	Uint32 last_jump;

	/* Sound */
	Mix_Chunk *sound;

public:
	Player(EventHandler *event_handler, Map *map, float x, float y);
	~Player();

	void TogglePaddle(unsigned);

	void NewMap(Map *map, float x, float y);
	void Damage(int d);

	/*EventListener*/
	void Notify(Event* e);
	int GetHP();
	void Landed();
};
 
#endif