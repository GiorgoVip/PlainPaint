#include "./headz/Window.h"
#include "./headz/Canvas.h"
#include "./headz/Bar.h"

#include "./basics.h"

// # @@@@@@@ # //
SDL_Event event;
struct
{
	Uint8 run : 1;
} appStatus;

int main(void)
{
	//SDL_Log(MI"Set the sails!\n");
	
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("SDL Failed to Initialize everything:'n%s",SDL_GetError()); //SDL_Log(ME"SDL Failed to Initialize everything:\n%s",SDL_GetError());
		return 1;
	}
	
	SDL_Log("SDL%i.%i.%i Successfully Initialized",SDL_MAJOR_VERSION,SDL_MINOR_VERSION,SDL_PATCHLEVEL);
	
	
	
	Canvas* canvas = CreateCanvas(800, 650);	// Create the canvas
	
	//Bar bar = CreateBar(250, 650);				// Create the bar
	
	appStatus.run = canvas->status.init;// && bar.status.init;
	// # APP SHOULD HAVE BEEN INITIALIZED # //
	
	//SDL_ShowSimpleMessageBox(0, "Kek", "Messagez", canvas->window);
	//FillCanvas(canvas);
int mx, my;
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
				/*case SDL_MOUSEBUTTONDOWN:
				{
					SDL_Log("Event Mouse Down rx: %i; ry: %i; s: %i;", event.button.x, event.button.y);
					PaintCanvas(canvas, event.button.x, event.button.y, (SDL_Color){255, 255, 255, 255});
					break;
				}
				case SDL_MOUSEMOTION:
				{
					SDL_Log("Event Mouse Motion rx: %i; ry: %i; s: %i; w: %i;", event.motion.x, event.motion.y, event.motion.state, canvas->surface->w);
					if(event.motion.state) PaintCanvas(canvas, event.motion.x, event.motion.y, (SDL_Color){255, 255, 255, 255});
					break;
				}*/
			}
		}
		SDL_PumpEvents();
		if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT))
			PaintCanvas(canvas, mx, my, (SDL_Color){255, 255, 255, 255});
	}
	//SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
	//SDL_RenderClear(ren);
	//
	//SDL_RenderPresent(ren);
	//SDL_Delay(3000);

	
	DestroyCanvas(canvas);
	//DestroyBar(bar);
	SDL_Quit();
	return 0;
}

// SDL2 downgrade and grab a few versions for windows etc
int testmain(int argc, char* argv[])
{
    SDL_Surface *screen; // even with SDL2, we can still bring ancient code back
    SDL_Window *window;
    SDL_Surface *image;
    
    
    SDL_Event event; int run = 1;

    SDL_Init(SDL_INIT_VIDEO); // init video

    // create the window like normal
    window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    // but instead of creating a renderer, we can draw directly to the screen
    screen = SDL_GetWindowSurface(window);

    // let's just show some classic code for reference
    image = SDL_LoadBMP("cancer.bmp"); // loads image
    SDL_BlitSurface(image, NULL, screen, NULL); // blit it to the screen

    // this works just like SDL_Flip() in SDL 1.2
    SDL_UpdateWindowSurface(window);
    while(run)
    {
		while(SDL_PollEvent(&event))
		{
			switch(event.type){
			case SDL_QUIT:
			{
				run = 0;
				break;
			}}
		}
	}
    
SDL_FreeSurface(image);
    // show image for 2 seconds
   // SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
