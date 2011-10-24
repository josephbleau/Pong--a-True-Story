#include "UIElementPaddleSelector.h"
#include "EventHandler.h"
#include "EventListener.h"
#include "Event.h"

UIElementPaddleSelector::UIElementPaddleSelector(EventHandler *event_handler, SDL_Surface *screen)
	: UIElement(event_handler)
{
	this->name = "PaddleSelector";
	this->screen = screen;
	this->surf = IMG_Load("c://data//paddle_ui.png");

	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 0;
	this->rect.h = 0;

	if(!this->surf)
		std::cerr << "Error loading PaddleSelector UI Element\n";
	else{
		this->rect.w = (Uint16) this->surf->w;
		this->rect.h = (Uint16) this->surf->h;
	}
	
}

UIElementPaddleSelector::~UIElementPaddleSelector()
{
	if(this->surf)
		SDL_FreeSurface(surf);
}

void UIElementPaddleSelector::Notify(Event *e)
{
	if(!e)
		return;
}