#include "ItemPlatformPaddle.h"
#include "Map.h"
#include "Paddle.h"
#include "ActorCollidedWithActorEvent.h"

ItemPlatformPaddle::ItemPlatformPaddle(EventHandler *event_handler, float x, float y, Map *map) :
Item(event_handler, x,y,IMG_Load("data//platpaddleitem.png"), map){
	this->uid = ACT_PLAT_PAD_ITEM;
}

ItemPlatformPaddle::~ItemPlatformPaddle()
{
}

void ItemPlatformPaddle::Notify(Event *e)
{
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR){
		ActorCollidedWithActorEvent *ae = (ActorCollidedWithActorEvent*) e;
		if(ae->GetActor1()->ID() == this->ID() &&
		   ae->GetActor2()->ID() == ACT_PLAYER){	
			this->Handler()->UnregisterListener(this);
			this->map->UnregisterActor(this);

			((Player*)ae->GetActor2())->TogglePaddle(PAD_PLATFORM);
		}
	}
}