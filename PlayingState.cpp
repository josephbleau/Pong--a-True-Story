#include "PlayingState.h"

#include <algorithm>

#include "conf.h"
#include "EventListener.h"

/*events -- */
#include "RenderEvent.h"
#include "SDLEvent.h"
#include "TickEvent.h"
#include "ItemAcquiredEvent.h"
#include "Game.h"
#include "MapChangeEvent.h"

/*ui elements -- */
#include "UIElementPaddleSelector.h"
#include "UIElementTextBox.h"

#include "Item.h"
#include "ItemPlatformPaddle.h"

#include <SDL/SDL_ttf.h>

PlayingState::PlayingState(Game *parent) : GameState( parent)
{
	this->state = STATE_PLAYING;
	this->map = new Map(this->Handler(), "data//test.tmx");
	this->map->Load(screen);

	this->player = new Player(this->map->Handler(), this->map, 
		                      this->map->SpawnX(), this->map->SpawnY());
	this->map->RegisterActor(player);


	/* Load UI Elements */

	/* TEMPORARY */
	SDL_Color fg;
	fg.r = 255;
	fg.g = 255;
	fg.b = 255;

	SDL_Color bg;
	bg.r = 0;
	bg.g = 0;
	bg.b = 0;

	std::string text = "    Pong, a True Story    ";
	TTF_Font *f = TTF_OpenFont("data//eartm.ttf", 34);
	this->mapnamesurf = TTF_RenderText(f, text.c_str(), fg, bg); 
	/* ---------- */
	
}

PlayingState::~PlayingState()
{
	this->Handler()->UnregisterListener(this);
}


void PlayingState::Notify(Event *e)
{
	if(!e)
		return;

	/* TODO: Map completion screen. */
	if(e->ID() == EVT_MAP_CHANGED)
	{
		MapChangeEvent *mce = (MapChangeEvent*) e;

		this->Handler()->ClearEvents();
		this->Handler()->UnregisterAll();
		this->Handler()->RegisterListener(this);

		this->last_map = this->map;
		this->last_map->RenderOff();

		this->map = new Map(this->Handler(), mce->Filename());
		this->map->Load(this->screen);

		this->player->NewMap(this->map, this->map->SpawnX(), this->map->SpawnX());
	}

	if(e->ID() == EVT_SDL){
		SDLEvent *se = (SDLEvent*) e;
		SDL_Event ev = se->GetSDLEvent();
		if(ev.type == SDL_KEYDOWN){
			if(ev.key.keysym.sym == SDLK_ESCAPE)
			{
				/* Enter Pause State */
			}
		}
	}
	

	if(e->ID() == EVT_ITEM_ACQUIRED)
	{
		ItemAcquiredEvent *iae = (ItemAcquiredEvent*) e;
		std::string text = " " + iae->Name() + "\n\n" + iae->Flavor() + "\n\n\n(space to close)";
		this->AddUIElement( new UIElementTextBox( this->map->Handler(), this->parent->Screen(), this, text) );
	}

}
void PlayingState::RenderOverlay(SDL_Surface *overlay)
{
	for(auto it = this->ui_elements.begin();
		it != this->ui_elements.end();
		it++)
	{
		(*it)->Draw();
	}	

	SDL_Rect fontrect;
	fontrect.x = 20;
	fontrect.y = 0;
	fontrect.w = 150;
	fontrect.h = 32;

	SDL_BlitSurface(this->mapnamesurf, NULL, overlay, &fontrect);
}

void PlayingState::AddUIElement(UIElement *ui)
{
	this->ui_elements.push_back(ui);
}

void PlayingState::RemoveUIElement(UIElement *ui)
{
	auto it = std::find(this->ui_elements.begin(),
		                this->ui_elements.end(),
						ui);

	if(it != this->ui_elements.end())
		this->ui_elements.erase(it);
}