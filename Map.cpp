#include "Map.h"

/* events -- */
#include "RenderEvent.h"
#include "PlayerMovedEvent.h"
#include "ActorCollidedWithActorEvent.h"
#include "TickEvent.h"
#include "MapChangeEvent.h"
#include "PlayerDiedEvent.h"
#include "SDLEvent.h"
#include "FallingTerrain.h"
#include "ItemCoin.h"
#include "SpikeTerrain.h"
#include "FallWhileUnderTerrain.h"
#include "conf.h"

#include "SDL/SDL_rotozoom.h"

Map::Map(EventHandler *event_handler,
	     std::string filename) : TMXMap(filename), 
		                         EventListener(event_handler)
{
	this->camera.x = 0;
	this->camera.y = 0;
	this->camera.w = SCREEN_WIDTH;
	this->camera.h = 1000; /* wtf fix later */
	std::cout << "height: " << SCREEN_HEIGHT << std::endl;
	this->map_surface = NULL;
	this->gravity = 5000;
	this->scale = 1;
	this->rendering_actors = true;
}

Map::~Map()
{
}

void Map::Load(SDL_Surface *screen)
{
	this->TMXLoad();
	this->LoadTileSurfaces(screen);
	this->LoadObjects();
	this->map_surface = this->GenerateMapSurface(screen);
}

void Map::LoadTileSurfaces(SDL_Surface *screen)
{
	int gid = 0;
	for( auto it = this->tilesets.begin();
		 it != this->tilesets.end();
		 it++ )
	{
		gid = (*it)->firstgid;

		if((*it)->image == NULL){
			std::cout << "No image for this tileset, bailed." << std::endl;
			break;
		}
		
		SDL_Surface *image_surf = IMG_Load(/*(*it)->image->source.c_str()*/ "data//cleantiles.png");
		if(image_surf == NULL){
			std::cout << "Unable to read image file " << (*it)->image->source << std::endl;
			break;
		}

		unsigned img_rows = image_surf->w  / (*it)->tileheight;
		unsigned img_cols = image_surf->h  /  (*it)->tilewidth;
	
		/* Cut out our tiles! */
		for( unsigned x = 0; x < img_rows; x++)
		{
			for( unsigned y = 0; y < img_cols; y++ )
			{
				SDL_Surface *surf = SDL_CreateRGBSurface(screen->flags, (*it)->tilewidth, (*it)->tileheight, 
					screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, 
					screen->format->Amask);

				this->tile_surfaces[gid++] = surf;

				SDL_Rect clip;
				clip.x = (Uint16) (x * (*it)->tilewidth);
				clip.y = (Uint16) (y * ((*it)->tileheight));
				clip.w = (Uint16) (*it)->tilewidth;
				clip.h = (Uint16) (*it)->tileheight;


				SDL_BlitSurface(image_surf, &clip, surf, NULL);
			}
		}
	}
}

void Map::LoadObjects()
{
	for(auto it = this->objectgroups.begin();
		it != this->objectgroups.end();
		it++)
	{
		for(auto objects = (*it)->objects.begin();
			objects != (*it)->objects.end();
			objects++)
		{
			if((*objects)->type == "actor")
				this->LoadActorObject(*objects);
			if((*objects)->type == "spawn")
				this->AddSpawnLocation(*objects);
			if((*objects)->type == "loadlevel")
				this->AddBoundary(*objects);
			if((*objects)->type == "death")
				this->AddBoundary(*objects);
			if((*objects)->type == "terrain")
				this->AddCustomTerrain(*objects);
		}
	}
}

void Map::LoadActorObject(TMXObject *actor)
{
	/* paddles -- */
	if(actor->properties["which"] == "platform_paddle_item"){
		ItemPlatformPaddle *paddle = new ItemPlatformPaddle(this->Handler(), 
		                                                (float) actor->x, 
							                            (float) actor->y, this);
	this->RegisterActor(paddle);
	}

	if(actor->properties["which"] == "reflect_paddle_item"){
		ItemReflectPaddle *paddle = new ItemReflectPaddle(this->Handler(), 
		                                                  (float) actor->x, 
							                              (float) actor->y, this);
		this->RegisterActor(paddle);
	}

	/* collectables -- */
	if(actor->properties["which"] == "coin_item"){
		ItemCoin *coin = new ItemCoin(this->Handler(), (float) actor->x, (float) actor->y, this);
		this->RegisterActor(coin);
	}

	/* enemies -- */
	if(actor->properties["which"] == "spitter_enemy"){
		Enemy *enemy = new Enemy((float) actor->x, (float) actor->y, this, this->Handler());
		this->RegisterActor(enemy);
	}
	
}

void Map::AddSpawnLocation(TMXObject *spawn)
{
	this->spawn_x = (float) spawn->x;
	this->spawn_y = (float) spawn->y;
}

void Map::AddBoundary(TMXObject *boundary)
{
	Boundary *b = new Boundary();
	b->x = (float) boundary->x;
	b->y = (float) boundary->y;
	b->w = (float) boundary->w;
	b->h = (float) boundary->h;
	b->name = boundary->properties["filename"];
	std::cout << b->name << std::endl;
	b->type = boundary->type;

	this->boundaries.push_back(b); 
}

void Map::AddCustomTerrain(TMXObject *terrain)
{
	SpecialTerrain *st = NULL;
	std::string prop = terrain->properties["property"];
	std::stringstream ss; // for conversions
	int tileno = -1;
	
	if(terrain->gid != -1){
		ss << terrain->gid;
		ss >> tileno;
		ss.clear();
	} else {
		tileno = 1;
	}

	SDL_Surface *sprite = this->tile_surfaces.at(tileno);
	
	if(prop == "spikes"){
		st = new SpikeTerrain((float)terrain->x,(float)terrain->y, this->Handler(), this);
	}
	else if(prop == "falling"){
		Uint32 delay;

		ss << terrain->properties["delay"];
		ss >> delay;
		ss.clear();

		st = new FallingTerrain((float)terrain->x,(float)terrain->y, this->Handler(), this, delay);
	}
	else if(prop == "fall_while_under"){
		Uint32 delay;

		ss << terrain->properties["delay"];
		ss >> delay;
		ss.clear();

		st = new FallWhileUnderTerrain((float)terrain->x, (float)terrain->y, this->Handler(), this,  delay);
	}

	if(sprite && st){
		st->SetSprite(sprite);
		this->RegisterActor(st);
	}
}

void Map::RenderMap(SDL_Surface *screen)
{
	if(!this->rendering_actors)
		return;

	SDL_Rect zoomed_camera = this->camera;
	if(scale != 1){
		if(scale < 1){
			zoomed_camera.x= (Sint16)(zoomed_camera.x / this->scale);
			zoomed_camera.y= (Sint16)(zoomed_camera.x / this->scale);
			zoomed_camera.w = (Sint16)(zoomed_camera.w /this->scale);
			zoomed_camera.h = (Sint16)(zoomed_camera.h / this->scale);
		}

		SDL_Surface *zoomed = zoomSurface(this->map_surface, this->scale, this->scale, 0);
		SDL_BlitSurface(zoomed, &zoomed_camera, screen, NULL);
		SDL_FreeSurface(zoomed);
	} else{
		SDL_BlitSurface(this->map_surface, &this->camera, screen, NULL);
	}
	/* Render all visible actors. */
	for( unsigned i = 0; i < this->actors.size(); i++ ){
		if(this->actors[i]->Hidden() == false)
		{
			float adjusted_x = 0;
			float adjusted_y = 0;
			
			if(this->scale != 1) {
				adjusted_x = float(this->actors[i]->X()*this->scale) - zoomed_camera.x;
				adjusted_y = float(this->actors[i]->Y()*this->scale) - zoomed_camera.y;
			} else {
				adjusted_x = this->actors[i]->X() - this->camera.x;
				adjusted_y = this->actors[i]->Y() - this->camera.y;
			}

			this->actors[i]->BlitTo(screen, adjusted_x, adjusted_y, this->scale);
		}
	}
}

void Map::Notify(Event *e)
{
	if(e->ID() == EVT_SDL)
	{
//		SDLEvent *sdlevent = (SDLEvent*)e;
//		SDL_Event se = sdlevent->GetSDLEvent();
		/* pondered adding some extra camera controll here */
	}

	if(e->ID() == EVT_TICK)
	{
		TickEvent *te = (TickEvent*) e;

		/* Apply gravity to all actors in the map. */
		for( auto it = this->actors.begin();
			 it != this->actors.end();
			 it++ )
		{
			if( (*it)->y_velocity < 400 && (*it)->GravityOn()){
				(*it)->y_velocity += (float) (this->gravity * float(te->Delta())/1000.0);
			}
		}
	}
	else if(e->ID() == EVT_RENDER)
	{
		RenderEvent *re = (RenderEvent*) e;
		this->RenderMap(re->Screen());

	}
	else if(e->ID() == EVT_PLAYER_MOVED)
	{
		PlayerMovedEvent *pme = (PlayerMovedEvent*) e;
		Player *p = pme->Who();

		int h = this->tileheight * this->height;
		int w = this->tilewidth * this->width;

		if( p->X() - SCREEN_WIDTH/2 > 0 &&
			p->X() + SCREEN_WIDTH/2 < w){
			this->camera.x = (Sint16) p->X() - SCREEN_WIDTH/2;
		}

		if(p->Y() - SCREEN_HEIGHT/2 < 0)
			this->camera.y = 0;
		else if(p->Y() + SCREEN_HEIGHT/2+p->H() > h)
			this->camera.y = (Sint16)(h - SCREEN_HEIGHT-p->H()); 
		else
			this->camera.y = (Sint16) (p->Y() - SCREEN_HEIGHT/2);
 		
	}
}

SDL_Surface *Map::GenerateMapSurface(SDL_Surface *screen)
{
	int pixw = this->width * this->tilewidth;
	int pixh = this->height * this->tileheight;

	SDL_Surface *map_surf = SDL_CreateRGBSurface( screen->flags, pixw, pixh, screen->format->BitsPerPixel,
		                                          screen->format->Rmask, screen->format->Gmask,
												  screen->format->Bmask, screen->format->Amask);

	if(map_surf == NULL) {
		std::cerr << "Error creating surface for map buffering! :(";
		return NULL;
	}

	for( auto it = this->layers.begin();
		 it != this->layers.end();
		 it++ )
	{

		unsigned c = 0;
		for( auto vit = (*it)->data.begin();
		     vit != (*it)->data.end();
			 vit++ )
		{
			SDL_Rect r;
			r.w = (Uint16) this->tilewidth;
			r.h = (Uint16) this->tileheight;
			r.y = (Uint16) ((c / this->width) * r.w);
			r.x = (Uint16) ((c % this->width) * r.h);

			if( (*it)->name != "Collision" ){
				if( this->tile_surfaces.find( *vit ) != this->tile_surfaces.end() ){
					if( this->tile_surfaces[*vit] != NULL )
					{
						SDL_BlitSurface( this->tile_surfaces[*vit], NULL, map_surf, &r);
					}
				}
			} else {
				if(*vit > 0)
					this->collision_map.push_back(true);
				else
					this->collision_map.push_back(false);
			}

			c++;
		}
	}

	return map_surf;
}

unsigned Map::GetCollisionIndex(float x, float y)
{
	unsigned index = ((unsigned) (y/this->tileheight) * this->width) + (unsigned) (x/this->tilewidth);

	if(index < this->collision_map.size())
		return index;

	return 0;
}

Actor *Map::IsCollidingWithActor(Actor *a)
{
	Actor *collided_with = NULL;

	for( unsigned i = 0; i < this->actors.size(); i++ )
	{
		if( this->actors[i]->ID() != a->ID() )
		{
			collided_with = (this->actors[i]->IsColliding(a)) ? this->actors[i] : NULL;

			if(collided_with){
				ActorCollidedWithActorEvent collide_event(a, this->actors[i]);
				this->Handler()->DispatchEvent(&collide_event);		
				break;
			}
		}
	}

	return collided_with;
}

CollisionAxis Map::IsColliding(float x, float y, float w, float h)
{
	CollisionAxis on = NO_COLLISION;

	/* A lot of nasty tom-foolery going on in here! Maybe someone smarter than me
	   will fix this, but it "works." */

	for( float i = x+1; i < x+w-1; i++){

		if( this->collision_map[ GetCollisionIndex( i, y ) ] ) 
			on = COLLISION_ALONG_Y_TOP;
		if( this->collision_map[ GetCollisionIndex( i, y+h) ] )
			on = COLLISION_ALONG_Y_BOTTOM;
	}
	
	for( float i = y+2; i < y+h-2; i++){
		if( this->collision_map[ GetCollisionIndex( x, i ) ] ||
			this->collision_map[ GetCollisionIndex( x+w, i ) ] )
			
			if(on != NO_COLLISION){
				if( (this->collision_map[ GetCollisionIndex(x,y-1)]   == 1  &&
					this->collision_map[ GetCollisionIndex(x+w,y-11)] == 1 ) || 
					(this->collision_map[ GetCollisionIndex(x,y+h+1)]   == 1  &&
					this->collision_map[ GetCollisionIndex(x+w,y+h+1)] == 1 ))
					on = COLLISION_ALONG_ALL;
				else 
					on = COLLISION_ALONG_X;
			}
			else
				on = COLLISION_ALONG_X;
	}

	return on;
}

void Map::BoundaryTest(float x, float y, float w, float h)
{
	/* Test collision against boundaries */
	for(auto it = this->boundaries.begin();
		it != this->boundaries.end(); 
		it++)
	{
		if( (y+h < (*it)->y || y > (*it)->y+(*it)->h) ||
			(x+w < (*it)->x ||x > (*it)->x+(*it)->w)){
				
		} else {
			if((*it)->type == "death"){
				this->CameraReset();
				PlayerDiedEvent pde;
				this->Handler()->DispatchEvent(&pde);
			}

			if((*it)->type == "loadlevel"){
				MapChangeEvent map_change((*it)->name);
				this->Handler()->DispatchEvent(&map_change);
			}
		}
	}
}

void Map::RegisterActor(Actor *a)
{
	this->actors.push_back(a);
}

void Map::UnregisterActor(Actor *a)
{
	this->Handler()->UnregisterListener(a);

	for(auto it = this->actors.begin();
		it != this->actors.end();
		it++)
	{
		if((*it) == a)
		{
			this->actors.erase(it);
			return;
		}
	}

	if(a)
		delete a;
}

SDL_Rect *Map::Camera(){return &this->camera; }

/* Print all of the maps information. */
void Map::PrintDebug()
{
	std::cout << "Map Debug Info: " << std::endl;
	std::cout << "\tMap " << this->filename << std::endl;
	std::cout << "\t\tVersion: " << this->version << std::endl;
	
	std::string orientation;
	if(this->orientation == ORTHOGONAL)
		orientation = "Orthogonal";
	else if(this->orientation == ISOMETRIC)
		orientation = "Isometric";

	std::cout << "\t\tOrientation: " << orientation << std::endl;
	std::cout << "\t\tWidth: " << this->width << std::endl;
	std::cout << "\t\tHeight: " << this->height << std::endl;
	std::cout << "\t\tTileWidth: " << this->tilewidth << std::endl;
	std::cout << "\t\tTileHeight: " << this->tileheight << std::endl;

	std::cout << "\t\tTilesets:" << std::endl;
	for( auto it = this->tilesets.begin();
		 it != this->tilesets.end();
		 it++)
	{
		std::cout << "\t\t\tfirstgid: " << (*it)->firstgid << std::endl;
		std::cout << "\t\t\tname: " << (*it)->name << std::endl;
		std::cout << "\t\t\timage: " << std::endl;
		std::cout << "\t\t\t\tsource: " << (*it)->image->source << std::endl;
		std::cout << "\t\t\t\theight: " << (*it)->image->height << std::endl;
		std::cout << "\t\t\t\twidth: " << (*it)->image->width<< std::endl;
	}

	std::cout << "\t\tLayers:" << std::endl;
	for( auto it = this->layers.begin();
		 it != this->layers.end();
		 it++)
	{
		std::cout << "\t\t\tname: " << (*it)->name << std::endl;
		std::cout << "\t\t\twidth: " << (*it)->width << std::endl;
		std::cout << "\t\t\theight: " << (*it)->height << std::endl;
		std::cout << "\t\t\tdata: " << std::endl;
		for( auto vit = (*it)->data.begin();
			 vit != (*it)->data.end();
			 vit++)
		{
			std::cout << *vit;
		}
	}
}

void Map::CameraReset()
{
	this->camera.x = 0;
	this->camera.y = 0;
}

std::string Map::Name(){ return this->filename; }
float Map::HeightInPx(){ return float(this->tileheight * this->height); }
float Map::SpawnX(){ return spawn_x; }
float Map::SpawnY(){ return spawn_y; }

void Map::RenderOff(){ this->rendering_actors = false; }