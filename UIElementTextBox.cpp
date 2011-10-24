#include "UIElementTextBox.h"
#include "conf.h"

#include "SDLEvent.h"
#include "PlayingState.h"
UIElementTextBox::UIElementTextBox(EventHandler *event_handler, SDL_Surface *screen,
	                               PlayingState *parent, std::string text)
	:UIElement(event_handler)
{
	this->name = "TextBox";
	this->screen = screen;
	this->rect.x = 150;
	this->rect.y = 150;
	this->rect.w = 300;
	this->rect.h = 250;
	this->parent = parent;

	this->parent->paused = true;

	this->surf = SDL_CreateRGBSurface( screen->flags, this->rect.w, this->rect.h,
		screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);
	
	SDL_FillRect(surf, &this->rect, 0x0);
	SDL_SetAlpha(surf,SDL_SRCALPHA, 0xbb);

	this->font = TTF_OpenFont("data//eartm.ttf",28);
	
	SDL_Color fg;
	fg.r = 255;
	fg.g = 255;
	fg.b = 255;

	SDL_Color bg;
	bg.r = 0;
	bg.g = 0;
	bg.b = 0;

	SDL_Rect fontrect;
	fontrect.x = 20;
	fontrect.y = 0;
	fontrect.w = 150;
	fontrect.h = 32;

	std::string buf = "";
	/*split our string up into portions of 30 characters */
	for(unsigned i = 0; i < text.size(); i++)
	{
		if(text[i] != '\n')
			buf += text[i];
		if(i % 30 == 0 || text[i] == '\n'){
			SDL_Surface *fontsurf = TTF_RenderText(font,buf.c_str(),fg, bg);
			SDL_BlitSurface(fontsurf, NULL, this->surf, &fontrect);
			if(i != 0)
				fontrect.y += 32;
			
			buf = "";
			SDL_FreeSurface(fontsurf);
		}
	}
			SDL_Surface *fontsurf = TTF_RenderText(font,buf.c_str(),fg, bg);
			SDL_BlitSurface(fontsurf, NULL, this->surf, &fontrect);
}

UIElementTextBox::~UIElementTextBox()
{

}

void UIElementTextBox::Notify(Event *e)
{
	if(e->ID() == EVT_SDL)
	{
		SDLEvent *se = (SDLEvent*)e;
		SDL_Event sdl_event = se->GetSDLEvent();

		if(sdl_event.type == SDL_KEYDOWN &&
		   sdl_event.key.keysym.sym == SDLK_SPACE)
		{

			this->parent->paused = false;
			this->parent->RemoveUIElement(this);
		}
	}
}