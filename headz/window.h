#include "../basics.h"

/*class Window
{
	protected:
	
	// # Properties # //
	SDL_Window* window;
	SDL_Renderer* ren;
	
	public:
	
	// # Methods # //
	Window(Uint16 w, Uint16 h, char* n)
	{
		if(!(window = SDL_CreateWindow(n, 0,0, w, h, 0)))
		{
			//SDL_LogError(ME"SDL Failed to CreateWindow:\n%s",SDL_GetError());
			SDL_Log("SDL Failed to Create %s Window:\n%s",n,SDL_GetError());
			//return 1;
		}
		if(!(ren = SDL_CreateRenderer(window, -1, 0)))
		{
			SDL_Log("SDL Failed to Create %s Renderer:\n%s",n,SDL_GetError());
		}
			
	}
	~Window()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(window);
	}
};*/

