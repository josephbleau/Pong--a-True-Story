#include "ItemReflectPaddle.h"
#include "Map.h"

#include "ActorCollidedWithActorEvent.h"

#include "Paddle.h"

ItemReflectPaddle::ItemReflectPaddle(EventHandler *event_handler, float x, float y, Map *map) :
Item(event_handler, x,y,IMG_Load("data//reflectpaddleitem.png"), map){
	this->uid = ACT_REF_PAD_ITEM;
}

ItemReflectPaddle::~ItemReflectPaddle()
{
}

void ItemReflectPaddle::Notify(Event *e)
{
	/*todo finish*/
	if(e->ID() == EVT_ACTOR_COLLIDED_WITH_ACTOR){
		ActorCollidedWithActorEvent *ae = (ActorCollidedWithActorEvent*) e;
		if(ae->GetActor1()->ID() == this->ID() &&
		   ae->GetActor2()->ID() == ACT_PLAYER){	
			this->Handler()->UnregisterListener(this);
			this->map->UnregisterActor(this);

			((Player*)ae->GetActor2())->TogglePaddle(PAD_REFLECT);
		}
	}
}