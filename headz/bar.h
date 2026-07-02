#include "./GUI.h"
// # Module Template # //
typedef struct
{
	// # Properties # //
	SDL_Window* window;
	SDL_Surface* surface;
	GUI* gui;
	struct
	{
		Uint8 init : 1;
		Uint8 dead : 1;
		
	} status;
	
}Bar;


// # Methods # //
Bar* CreateBar(Uint16 w, Uint16 h)
{
	Bar* self = malloc(sizeof(Bar));
	
	if(!(self->window = SDL_CreateWindow("Bar", 0,0, w, h, 0)))
	
		SDL_Log("SDL Failed to Create Bar Window:\n%s",SDL_GetError());

	if(!(self->surface = SDL_GetWindowSurface(self->window)))

		SDL_Log("SDL Failed to Get Window Surface for Bar:\n%s",SDL_GetError());
	
	if(!(self->gui = CreateGUI(self->surface)))
	
		SDL_Log("Failed to Create a GUI for Bar");
	
	self->status.dead = 0;	self->status.init = 1; // Initialized successfully
	SDL_Log("Initialized Bar successfully");
	return self;
}

void DestroyBar(Bar* self)
{
	self->status.dead = 1;;;
	
	DestroyGUI(self->gui);
	SDL_DestroyWindow(self->window);
	
	free(self);
}


void Placey(Bar* self, Uint32 x, Uint32 y, SDL_Surface* sur, Uint32 scale)
{	Uint32 xs = 0, ys = 0;
	for(Uint32 xc = 0; xc != sur->w * scale; ++xc)
		for(Uint32 yc = 0; yc != sur->h * scale; ++yc)
		{
			*((Uint32*)self->surface->pixels + ((xc+x) + ((yc+y)*self->surface->w))) = *(  (Uint32*)sur->pixels + ( xc / scale + (yc / scale * sur->w) )  );
		}
	SDL_UpdateWindowSurface(self->surface);
}

void UpdateBar(Bar* self)
{
	UpdateGUI(self->gui);
	
	SDL_UpdateWindowSurface(self->window);
}

void TestGUI(Bar* self)
{
	///PlaceIconGUI(self->gui, _ICON_WARN, 0, 0);
	
	SDL_UpdateWindowSurface(self->window);
}

