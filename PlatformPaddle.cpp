#include "PlatformPaddle.h"
#include "Map.h"

#include "RenderEvent.h"
#include "ActorCollidedWithActorEvent.h"

PlatformPaddle::PlatformPaddle(EventHandler *event_handler, Map *map, float x, float y ) :
Paddle(event_handler, map, x, y, IMG_Load("data//platform_paddle.png"))
{
	this->sprite_y = 15;
	this->sprite_h = -10;
	this->type = PAD_PLATFORM;
}

PlatformPaddle::~PlatformPaddle()
{

}

void PlatformPaddle::Notify(Event *e)
{
	if(e->ID() == EVT_RENDER)
	{
		/* Handled by Map::MapRender */
	}
}

