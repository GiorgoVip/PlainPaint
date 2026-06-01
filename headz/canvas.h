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
	
}Canvas;


// # Methods # //
Canvas* CreateCanvas(Uint16 w, Uint16 h)
{
	Canvas* self = malloc(sizeof(Canvas));
	
	if(!(self->window = SDL_CreateWindow("Canvas", 0,0, w, h, SDL_WINDOW_RESIZABLE)))
	
		SDL_Log("SDL Failed to Create Canvas Window:\n%s",SDL_GetError());

	if(!(self->surface = SDL_GetWindowSurface(self->window)))

		SDL_Log("SDL Failed to Get Window Surface for Canvas:\n%s",SDL_GetError());
	
	self->status.init = 1; // Initialized successfully
	SDL_Log("Initialized Canvas successfully");
	return self;
}

void DestroyCanvas(Canvas* self)
{
	SDL_DestroyWindow(self->window);
	free(self);
}

void FillCanvas(Canvas* self)
{	SDL_PixelFormat* format = self->surface->format; Uint32 p = SDL_MapRGBA(format, 255, 255, 0, 255);
	for(int y = 0; y <= self->surface->h; ++y)
		for(int x = 0; x <= self->surface->w; ++x)
		{
			SDL_Log("FillCanvas: w: %i; h: %i; x: %i; y: %i; i: %i;", self->surface->w, self->surface->h, x, y, (x + (y*self->surface->w)));
			*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = p;//x % 256;
		}

	SDL_UpdateWindowSurface(self->window);
}

void PaintCanvas(Canvas* self, Uint32 x, Uint32 y, SDL_Color c)
{
	*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = 0xffffffff;//SDL_MapRGBA(self->surface->format, c.r, c.g, c.b, c.a);
	*((Uint32*)self->surface->pixels + (x+1 + (y*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x-1 + (y*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x + ((y+1)*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x + ((y-1)*self->surface->w))) = 0xffffffff;
	SDL_UpdateWindowSurface(self->window);
}
