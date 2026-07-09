#include "./font.h"

// # Executable Internal Graphics # //


// # Icon Graphics Settings # //

#define _ICON_WIDTH  ((Uint8) 16 )
#define _ICON_HEIGHT  _ICON_WIDTH

///GUIIcon _ICON_BNK[8];

// # Warning Icon # //

///	Unused, 'Icons' will be loaded from the provided 'Icons Bundle' via 'SDL_LoadBMP'

/**static SDL_Surface* SliceIcons(DynamicArray* list, SDL_Surface* surface, SDL_Rect slice)
{
	
	
	
	
	
}*/

///typedef struct {	char* names; GUIIcon* icons;	} GUIIconList;

DynamicArray* LoadIcons(SDL_PixelFormat* format, char* names)			/// Does NOT check wether there actual names!!! '%' = end of names	ONLY USE ONE NUL TERMINATOR PER NAME
{
	SDL_Surface* surface;
	DynamicArray* icons = CreateDynamicArray(0, sizeof(SDL_Surface*));///sizeof(GUIIcon));
	Uint32 seek = 0, cname = 0;											/// seek explores each character while cname captures each name by staying behind
	
	while(names[seek] != '%')
	{
		if(names[seek] == '\0')
		{
			SDL_Log("Loading: %s\n",names + cname);
			
			surface = SDL_ConvertSurface(SDL_LoadBMP(names + cname), format, 0);
			PushInDynamicArray(icons, &surface);///&(GUIIcon){surface->w, surface->h, surface->pixels});	/// surface needs to bee free'd too
			
			cname = seek + 1;	/// Only one NUL per name
		}
		
		++seek;
	}
		
	SDL_Log("Done Loading Icons"); return icons;
}
	
	

void DestroyIcons(DynamicArray* icons)
{
	for(Uint8 c = 0; c != icons->amount; ++c)
		SDL_FreeSurface(((SDL_Surface**)icons->data)[c]);
	DestroyDynamicArray(icons);
}
