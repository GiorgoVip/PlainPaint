#include "../basics.h"

typedef struct
{
	// # Properties # //
	SDL_Surface* surface;
	struct
	{
		Uint8 init : 1;
		//Uint8 dead : 1;
		
	} status;
	
}GUI;


// # Methods # //
GUI* CreateGUI(SDL_Surface* surface)
{
	GUI* self = malloc(sizeof(GUI));
	
	if(!(self->surface)))

		SDL_Log("No Surface provided for \"CreateGui\"");
	
	self->status.init = 1; // Initialized successfully
	SDL_Log("Initialized GUI successfully");
	return self;
}

void DestroyGUI(GUI* self)
{
	free(self);
}


typedef enum
{
	GUI_TEXT = 0,
	GUI_BUTTON = 1,
	GUI_IMAGE = 2,
} GUIElementType;


typedef struct
{
	GUI* gui;
	GUIElementType type;
	///
} fuck;
	
