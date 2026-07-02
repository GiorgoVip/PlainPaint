#include "./basics.h"

#include "./globals.h"

#include "./headz/Window.h"
#include "./headz/Canvas.h"
#include "./headz/Bar.h"

#include "./headz/3rd/XiaoLine.h"

#include "./Resources/internal.h"

int main(void)
{
	///SDL_Log(MI"Set the sails!\n");
	
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("SDL Failed to Initialize everything:'n%s",SDL_GetError()); ///SDL_Log(ME"SDL Failed to Initialize everything:\n%s",SDL_GetError());
		return 1;
	}
	
	SDL_Log("SDL%i.%i.%i Successfully Initialized",SDL_MAJOR_VERSION,SDL_MINOR_VERSION,SDL_PATCHLEVEL);
	
	
	// # APP MODULES INITIALIZATION # //
	
	
	Canvas* canvas = CreateCanvas(800, 650);	/// Create the canvas
	
	Bar* bar = CreateBar(250, 650);				/// Create the bar
	
	DynamicArray* s = _UnpackIcons(bar->surface->format, "/Users/bobkins/Documents/raboti/Stuffings/PlainPaint/tet.bmp\0%", 10);
	
				PlaceGUI(bar->gui, ""
			
			"___ Hello world ___"
			"[ click me ]"
			"-> normalBrush ;"
			
			);
	
	appStatus.run = canvas->status.init && bar->status.init;
	
	
	// # LOCAL APP VARIABLES # //
	
	int mx, my;									/// Current Mouse Postions
	
	
	// # APP PRE-RENDERING # //
	
	FillCanvas(canvas, (SDL_Color){255, 255, 255, 255});
	
	
	// # APP UPDATE ROUTINE # //

	while(appStatus.run)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					SDL_Log("Event Quit...");
					appStatus.run = 0;
					break;
				}
			}
		}
		
		SDL_PumpEvents();
		if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT))
			PaintCanvas(canvas, mx, my, (SDL_Color){255, 255, 255, 255}),
			LineCanvas(canvas, 400, 325, mx, my, (SDL_Color){255, 255, 255, 90});
		SDL_Surface* ptr = *(SDL_Surface**)s->data;

			 Placey(bar, 0, 0, ptr, 10);
		 SDL_UpdateWindowSurface(bar->window);
	}
	//SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
	//SDL_RenderClear(ren);
	//
	//SDL_RenderPresent(ren);
	//SDL_Delay(3000);

_DestroyIcons(s);
	DestroyBar(bar);
	DestroyCanvas(canvas);
	SDL_Quit();
	return 0;
}

// SDL2 downgrade and grab a few versions for windows etc
