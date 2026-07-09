#include "./basics.h"

// # Application Globals # //

SDL_Event event;

struct
{
	Uint8 run : 1;
	///
} appStatus;

Uint8 barFocus = 0;															// Time shortage issues

SDL_Color CanvasBackgroundColor = (SDL_Color){255, 255, 255, 255};

