#include "../basics.h"

typedef struct
{
	// # Properties # //
	SDL_Window* window;
	SDL_Surface* surface;
	struct
	{
		Uint8 init : 1;
		//Uint8 dead : 1;
		
	} status;
	
}Bar;


// # Methods # //
Bar* CreateBar(Uint16 w, Uint16 h)
{
	Canvas* self = malloc(sizeof(Bar));
	
	if(!(self->window = SDL_CreateWindow("Bar", 0,0, w, h, 0)))
	
		SDL_Log("SDL Failed to Create Bar Window:\n%s",SDL_GetError());

	if(!(self->surface = SDL_GetWindowSurface(self->window)))

		SDL_Log("SDL Failed to Get Window Surface for Bar:\n%s",SDL_GetError());
	
	self->status.init = 1; // Initialized successfully
	SDL_Log("Initialized Bar successfully");
	return self;
}

void DestroyBar(Bar* self)
{
	SDL_DestroyWindow(self->window);
	free(self);
}
