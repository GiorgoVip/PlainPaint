#include "../basics.h"
#include "./extra.h"
typedef struct	// # Module Template # //
{
	// # Properties # //
	SDL_Window* window;
	SDL_Surface* surface;
	struct
	{
		Uint8 init : 1;
		///Uint8 dead : 1;
		
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

// # Canvas Rendering Methods # //
void FillCanvas(Canvas* self, SDL_Color c)
{	
	SDL_PixelFormat* format = self->surface->format; Uint32 p = SDL_MapRGBA(format, 255, 0, 255, 255);
	/**for(int y = 0; y <= self->surface->h; ++y)
		for(int x = 0; x <= self->surface->w; ++x)
		{
			SDL_Log("FillCanvas: w: %i; h: %i; x: %i; y: %i; i: %i;", self->surface->w, self->surface->h, x, y, (x + (y*self->surface->w)));
			*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = p;//x % 256;
		}
	*/
	for(int i = 0; i <= self->surface->h * self->surface->w; ++i) *((Uint32*)self->surface->pixels + (i)) = p;

	SDL_UpdateWindowSurface(self->window);
}

void PaintCanvas(Canvas* self, Uint32 x, Uint32 y, SDL_Color c)
{
	*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = 0x00ffffff;///SDL_MapRGBA(self->surface->format, c.r, c.g, c.b, c.a);
/**	*((Uint32*)self->surface->pixels + (x+1 + (y*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x-1 + (y*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x + ((y+1)*self->surface->w))) = 0xffffffff;
	*((Uint32*)self->surface->pixels + (x + ((y-1)*self->surface->w))) = 0xffffffff;*/
	SDL_UpdateWindowSurface(self->window);
}

void PutDPixelCanvas(Canvas* self, Uint32 x, Uint32 y, Uint32 p)
{
	*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = p;
}

void PutPixelCanvas(Canvas* self, Uint32 x, Uint32 y, SDL_Color c)
{
	*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = SDL_MapRGB(self->surface->format, c.r, c.g, c.b);
}

Uint32 ColTrnCanvas(Canvas* self, Uint8 rd, Uint8 gd, Uint8 bd, Uint8 ad , Uint8 rs, Uint8 gs, Uint8 bs, Uint8 as) /// InBetween Conversion
{
	return SDL_MapRGB(self->surface->format, rd + (rs - rd) / 255 * as, gd + (gs - gd) / 255 * as, bd + (bs - bd) / 255 * as);
}

void PutTPixelCanvas(Canvas* self, Uint32 x, Uint32 y, SDL_Color c)
{
	Uint32* loc = ((Uint32*)self->surface->pixels + (x + (y*self->surface->w)));
	SDL_Color oc; SDL_GetRGB(*loc, self->surface->format, &oc.r, &oc.g, &oc.b); ///oc.a = 255;
	*loc = ColTrnCanvas(self, oc.r, oc.g, oc.b, 255 , c.r, c.g, c.b, c.a);
}

void LineCanvas(Canvas* self, Uint32 bx, Uint32 by, Uint32 ex, Uint32 ey, SDL_Color c)
{
	Sint32 x = ex - bx;
	Sint32 y = ey - by;
	
	
	if(SDL_abs(x) > SDL_abs(y))
	{
		float ys = (float)y / (float)x;
		
		for(Sint32 s = 0;  s != x  && 1; s += GetSignNumber(x))
			PutTPixelCanvas(self, bx + s, by + s * ys, c);
	}
	else // 0 or y > x
	{
		float xs = (float)x / (float)y;
		
		for(Sint32 s = 0; s != y && 1; s += GetSignNumber(y))
			PutTPixelCanvas(self, bx + s * xs, by + s, c);
	}
	
	/**for(Sint32 s = bx; s != ex; s += sgn(x))
		PutPixelCanvas(self, s, ey, c);
	for(Sint32 s = ey; s != by; s -= sgn(y))
		PutPixelCanvas(self, ex, s, c);*/
	
	SDL_UpdateWindowSurface(self->surface);
}

void BlorbCanvas(Canvas* self, Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
	for(Uint32 xc = x; xc != x+w; ++xc)
		for(Uint32 yc = y; yc != y+h; ++yc)

			PutPixelCanvas(self, xc, yc, (SDL_Color){255, 255, 255});
			
	SDL_UpdateWindowSurface(self->surface);
}

