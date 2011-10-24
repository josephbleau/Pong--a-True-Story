#include "Player.h"
#include "EventHandler.h"
#include "Map.h"
#include "PlatformPaddle.h"
#include "ReflectPaddle.h"

#include "Projectile.h"

/* events -- */
#include "PlayerMovedEvent.h"
#include "RenderEvent.h"
#include "SDLEvent.h"
#include "TickEvent.h"
#include "ItemAcquiredEvent.h"
#include "PlayerDiedEvent.h"
#include "ActorCollidedWithActorEvent.h"

#include "conf.h"

Player::Player(EventHandler *event_handler, Map *map, float x, float y) : 
Actor(x, y-60, IMG_Load("data//pong.png"), map, event_handler)
{
	this->spawn_x = x;
	this->spawn_y = y;
	this->sprite_x = 25;
	this->sprite_y = 33;
	this->sprite_w = -60;
	this->sprite_h = -32;
	this->uid = ACT_PLAYER;
	this->hp = 10;
	this->last_hurt = SDL_GetTicks();

	this->sound = Mix_LoadWAV("data//snd//jump.wav");
}

Player::~Player()
{

}

void Player::NewMap(Map *map, float x, float y)
{
	this->x = x;
	this->y = y;
	this->spawn_x = x;
	this->spawn_y = y;

	this->map->UnregisterActor(this);
	this->map = map;
	this->map->RegisterActor(this);
	this->map->Handler()->RegisterListener(this);
}

void Player::Notify(Event *e)
{
	switch(e->ID())
	{
		case EVT_ACTOR_COLLIDED_WITH_ACTOR:
		{
			ActorCollidedWithActorEvent *ae = (ActorCollidedWithActorEvent*) e;
			if(ae->GetActor1() == this &&
			   ae->GetActor2()->ID() == ACT_PROJECTILE)
			{
				int damage =  ((Projectile*)ae->GetActor2())->GetDamage();
				this->Damage(damage);
			}
			break;
		}

		case EVT_PLAYER_DIED:
		{
			this->hp = 10;

			this->x_velocity = 0;
			this->y_velocity = 0;
			
			this->last_hurt = 0;

			this->x = this->spawn_x;
			this->y = this->spawn_y;
			
			/*remove your paddles when you die*/
			for( auto it = this->paddles.begin(); 
				 it != this->paddles.end(); 
				 it++ )
			{
				delete (*it);
			}
			paddles.clear();

			break;
		}

		case EVT_TICK:
		{
			TickEvent *te = (TickEvent*) e;
			float delta = (float) te->Delta();

			CollisionAxis outcome = this->UpdateLocation((TickEvent *) e);
			if( outcome != COLLISION_ALONG_ALL )
			{
				PlayerMovedEvent pme(this);
				this->Handler()->DispatchEvent(&pme);
			} 

			/* Keys we care about on a per-tick basis check hurr! */
			Uint8 *keystates = SDL_GetKeyState( NULL );

			if(!this->falling && keystates[SDLK_w])
			{
				if(this->SinceLanded() > 75){	// cant jump until 75ms after landing
//					Mix_PlayChannel(-1, this->sound, 0);
					this->falling = true;
					this->y_velocity = -1000;
				}
			}

			/* Calculate appropriate velocities based on which
			    keys to move we're holding! :) */
			bool move_keys_down = false;
			if( (keystates[SDLK_LEFT] || keystates[SDLK_a]) ){
				move_keys_down = true;
				if(this->x_velocity > -500)
					this->x_velocity -= float(1400.0 * delta/1000.0);
				if(this->x_velocity > 0)
					this->x_velocity -= float(42000.0 *delta/1000.0);
			}
			if( (keystates[SDLK_RIGHT] || keystates[SDLK_d]) ){
				move_keys_down = true;
				if(this->x_velocity < 500)
					this->x_velocity += float(1400.0 * delta/1000.0);
				if(this->x_velocity < 0)
					this->x_velocity += float(42000.0 * delta/1000.0);
			}
			
			if(!move_keys_down){ // no keys being pressed, slow down!
				if( this->x_velocity > 0 ) {
					this->x_velocity -= float(5600.0 * delta/1000.0);
					if( this->x_velocity< 0)
						this->x_velocity = 0;
				} else {
					this->x_velocity += float(5600.0 * delta/1000.0);
					if( this->x_velocity > 0)
						this->x_velocity = 0;
				}
			}

			/* Test to see if we landed in any boundaries on the map, aka for death or loading
			   new levels. */
			this->map->BoundaryTest(this->SX(), this->SY(), this->SW(), this->SH());
			
			break;
		}
		case EVT_RENDER:
		{
			/* Handled by Map::RenderMap */
			break;
		}
		case EVT_SDL:
		{
			SDL_Event sdl_event = ((SDLEvent*) e)->GetSDLEvent();
			
			/* If interested in a key press, check here for it. */
			switch(sdl_event.type)
			{
				case SDL_KEYDOWN:
				{
					//int sym = sdl_event.key.keysym.sym;
				}
				break;
				case SDL_MOUSEBUTTONDOWN:
				{
					int button = sdl_event.button.button;
					
					float mx = sdl_event.motion.x + (float) this->map->Camera()->x-8;
					float my = sdl_event.motion.y + (float) this->map->Camera()->y-8;	

					if(mx >= this->x && mx <= this->x + this->W() &&
					   my >= this->y && my <= this->y + this->H()){
						/* todo: some sort of error noise */
						std::cerr << "Attempted to place paddle on self\n";
						break;
					}

					Paddle *p = NULL;

					if(button == 1 && this->usable_paddles["platform"])
					{
						if(this->paddles.size() == 2){
							this->map->UnregisterActor(*this->paddles.begin());
							this->paddles.erase(this->paddles.begin());
						}

						p = new PlatformPaddle(this->Handler(), this->map, mx, my);
					}
					else if(button == 3 && this->usable_paddles["reflect"])
					{
						if(this->paddles.size() == 2){;
							this->map->UnregisterActor(*this->paddles.begin());
							this->paddles.erase(this->paddles.begin());
						}

						p = new ReflectPaddle(this->Handler(), this->map, mx, my);
						
					}

					if(p){
						this->paddles.push_back(p);
						this->map->RegisterActor(p);
					}

				}
			} /* end of switch(sdl.event.type) */

			break;
		} /* end of case EVT_SDL */
		default: 
		{
			break;
		}
	} /* end of switch(e->ID()) */
}

void Player::TogglePaddle(unsigned paddle)
{
	/* Platform paddle enabled */
	switch(paddle){
		case PAD_PLATFORM:
		{
			this->usable_paddles["platform"] = true;
			ItemAcquiredEvent iae("Platform Paddle", "Left click to use it.");

			this->Handler()->DispatchEvent(&iae);
			break;	
		}
		case PAD_REFLECT:
		{
			this->usable_paddles["reflect"] = true;
			ItemAcquiredEvent iae("Reflect Paddle", "Right click to use it.");

			this->Handler()->DispatchEvent(&iae);
			break;
		}
	}
}

void Player::Damage(int d)
{
	if(SDL_GetTicks() - this->last_hurt > 1500){
		this->map->pg.GenerateBloodSplatter(this->x+this->W()/2, this->SY(), this->map);
		this->hp -= d;
		this->last_hurt = SDL_GetTicks();

		if(this->hp <= 0){
			this->map->CameraReset();
			PlayerDiedEvent pde;
			this->Handler()->DispatchEvent(&pde);
		}
	}
} 

int Player::GetHP(){ return this->hp; }