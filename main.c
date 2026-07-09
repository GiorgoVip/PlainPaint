#include "./basics.h"
#include "./globals.h"


#include "./headz/extra.h"
#include "./headz/equipment.h"

#include "./headz/Canvas.h"
#include "./headz/GUI.h"
#include "./headz/Bar.h"


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
	
	DynamicArray* s = LoadIcons(bar->surface->format, "/Users/bobkins/Documents/raboti/Stuffings/PlainPaint/tet.bmp\0%");
	
				PlaceGUI(bar->gui, ""
			
			"___ Hello world ___"
			"/SAVE<>LOAD\\"
			"[SAVE WORK]"
			"-< 0;"
			"[LOAD WORK]"
			"-< 1;"
			"-V;"
			"[TEST_ERASER]"
			"->1;"
			"-V  0  ;"
			"/BRUSHES\\"
			
			);	PlaceEquipmentButtons(bar->gui);
	
	appStatus.run = canvas->status.init && bar->status.init;
	
	
	// # LOCAL APP VARIABLES # //
	
	int mx, my;									/// Current Mouse Postions
	int pmx = 0, pmy = 0;								/// Previous Mouse Positions
	
	Uint8 drawing = 0;
	
	// # APP PRE-RENDERING # //
	
	FillCanvas(canvas, CanvasBackgroundColor);
	FillGUI(bar->gui, (SDL_Color){0, 0, 0, 255}); UpdateElementsGUI(bar->gui, bar->gui->root, 0); SDL_UpdateWindowSurface(bar->window);
	
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
				
				case SDL_WINDOWEVENT:									// Time Shortage ISSues
				{
					if(event.window.event == SDL_WINDOWEVENT_ENTER)
						barFocus = (SDL_GetWindowID(bar->window) == event.window.windowID);/// SDL_Log("%i", barFocus);
					break;
				}
			}
		}
		
		SDL_PumpEvents();
	
		/// # CANVAS # ///
		
		if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT))	/// PaintCanvas(canvas, mx, my, (SDL_Color){255, 255, 0, 255});
		{
			if(pmx && pmy) LineCircleCanvas(canvas, pmx, pmy, mx, my, CurrentEquipment->size, CurrentEquipment->color);///LineCanvas(canvas, pmx, pmy, mx, my, (SDL_Color){255, 255, 255, 90});
			pmx = mx;
			pmy = my;
		}
		else
		{
			pmx = 0;
			pmy = 0;
		}
			
		/// # BAR # ///
		
		///SDL_Surface* ptr = *(SDL_Surface**)s->data;
		
		UpdateGUI(bar->gui, canvas);

			 
		SDL_UpdateWindowSurface(canvas->window);
		SDL_UpdateWindowSurface(bar->window);
	}
	///SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
	///SDL_RenderClear(ren);
	///
	///SDL_RenderPresent(ren);
	///SDL_Delay(3000);

	DestroyIcons(s);	CleanGUIContainer(bar->gui->root);
	DestroyBar(bar);
	DestroyCanvas(canvas);
	SDL_Quit();
	return 0;
}

/// SDL2 downgrade and grab a few versions for windows etc
