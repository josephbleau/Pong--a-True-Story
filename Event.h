#ifndef EVENT_H
#define EVENT_H

enum EventID { EVT_GENERIC = 0, EVT_RENDER, EVT_TICK,
	           EVT_PLAYER, EVT_SDL, EVT_MAP_CHANGED, EVT_PLAYER_MOVED,
			   EVT_PLAYER_COLLIDED_WITH_MAP, EVT_ACTOR_COLLIDED_WITH_ACTOR,
               EVT_ITEM_ACQUIRED, EVT_PLAYER_DIED };

class Event
{
private:
	EventID id;

public:
	Event();
	Event(EventID id);

	~Event();

	EventID ID();
};

#endif