#include "ReflectPaddle.h"
#include "Map.h"

#include "RenderEvent.h"
#include "ActorCollidedWithActorEvent.h"

ReflectPaddle::ReflectPaddle(EventHandler *event_handler, Map *map, float x, float y ) :
Paddle(event_handler, map, x, y, IMG_Load("data//reflect_paddle.png"))
{
	this->type = PAD_REFLECT;
	this->ethereal = true;
	this->uid = ACT_REF_PAD;
}


ReflectPaddle::~ReflectPaddle()
{

}

void ReflectPaddle::Notify(Event *e)
{
	if(e->ID() == EVT_RENDER)
	{
		/* Handled by Map::MapRender */
	}
}

