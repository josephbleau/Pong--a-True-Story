#include "ItemCoin.h"
#include "Map.h"
#include "Paddle.h"
#include "ActorCollidedWithActorEvent.h"

ItemCoin::ItemCoin(EventHandler *event_handler, float x, float y, Map *map) :
Item(event_handler, x,y,IMG_Load("data//coin.png"), map){
	this->uid = ACT_PLAT_PAD_ITEM;
}

ItemCoin::~ItemCoin()
{
}

void ItemCoin::Notify(Event *e)
{
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR){
		ActorCollidedWithActorEvent *ae = (ActorCollidedWithActorEvent*) e;
		if(ae->GetActor1() == this &&
		   ae->GetActor2()->ID() == ACT_PLAYER){	
			this->Handler()->UnregisterListener(this);
			this->map->UnregisterActor(this);

			//TODO: Keep track of how many coins we've collected.
		}
	}
}