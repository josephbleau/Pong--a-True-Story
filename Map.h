#ifndef MAP_H
#define MAP_H

#include <string>
#include <map>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Actor.h"
#include "Event.h"
#include "Enemy.h"
#include "Item.h"
#include "ItemPlatformPaddle.h"
#include "ItemReflectPaddle.h"
#include "EventListener.h"
#include "EventHandler.h"
#include "TMXLoader/TMXMap.h"
#include "ParticleGenerator.h"
#include "Vec2d.h"

enum CollisionAxis { NO_COLLISION = 0, COLLISION_ALONG_X, 
	                 COLLISION_ALONG_Y_TOP, COLLISION_ALONG_Y_BOTTOM,
                     COLLISION_ALONG_ALL };

struct Boundary{ 
	std::string name; 
	std::string type;
	float x, y, w, h; 
};

class Map : public EventListener, public TMXMap
{
protected:
	SDL_Surface *map_surface;

	std::map<unsigned, SDL_Surface*> tile_surfaces;
	
	std::vector<bool> collision_map;
	unsigned GetCollisionIndex(float x, float y);

	std::vector<Actor*> actors;
	std::vector<Boundary*> boundaries;

	SDL_Rect camera;

	float gravity;
	float spawn_x, spawn_y;
	double scale;

	void AddCustomTerrain(TMXObject *terrain);
	void AddSpawnLocation(TMXObject *spawn);
	void AddBoundary(TMXObject *boundary);
	void LoadTileSurfaces(SDL_Surface *screen);
	void LoadObjects();
	void LoadActorObject(TMXObject *actor);

	SDL_Surface *GenerateMapSurface(SDL_Surface *screen);

	bool rendering_actors;

public:
	Map(EventHandler *event_handler, std::string filename);
	~Map();

	ParticleGenerator pg;

	void RenderMap(SDL_Surface *screen);
	void Load(SDL_Surface *screen);
	void Notify(Event *e);
	void PrintDebug();

	Actor *IsCollidingWithActor(Actor *a);
	CollisionAxis IsColliding(float x, float y, float w, float h);
	void BoundaryTest(float x, float y, float w, float h);

	void RegisterActor(Actor *a);
	void UnregisterActor(Actor *a);

	SDL_Rect *Camera();
	void CameraReset();

	std::string Name();
	float HeightInPx();
	float SpawnX();
	float SpawnY();
	void RenderOff();
};

#endif