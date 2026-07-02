#include "../basics.h"

// # Structures # //

typedef enum
{
	GUI_STATIC = 0b01,
	GUI_INTERACT = 0b10,
	GUI_CONTAINER = 0b00,

} GUIElementType;



typedef struct
{
	GUIElementType type;
	
	char* txt;															/// Could also be used for misc. data
	void* dat;															/// Could be used to contain Icons and other Elements & Containers
	
	Uint32 amount;
	Uint32 current;														/// Could be used for animations and different icon states
	///
} GUIElement;


typedef GUIElement GUIContainer;


typedef struct
{
	// # Properties # //
	SDL_Surface* surface;
	GUIContainer* root;
	struct
	{
		Uint8 init : 1;
		Uint8 dead : 1;
		Uint8 busy : 1;
		
	} status;
}GUI;
	

// # Methods # //
GUI* CreateGUI(SDL_Surface* surface)
{
	GUI* self = malloc(sizeof(GUI));
	
	if(!(surface))
	{
		SDL_Log("No Surface provided for \"CreateGui\"");
		return (GUI*)0;
	}
	self->surface = surface;
	
	self->root = malloc(sizeof(GUIContainer));	self->root->type = GUI_CONTAINER;
	
	self->status.dead = 0;  self->status.busy = 0;  self->status.init = 1; // Initialized successfully
	
	SDL_Log("Initialized GUI successfully");
	return self;
}

void DestroyGUI(GUI* self)
{
	self->status.dead = 1;
	free(self->root);
	free(self);
}

void CleanGUIContainer(GUIContainer* root)
{
	SDL_Log("GUI Cleaning %s GUIContainer\n", root->txt);
	
	for(Uint32 c = 0; c != root->amount; ++c)
	{
		if( ((GUIContainer*)root->dat)[c]->type == GUI_CONTAINER )
		{
			CleanGUIContainer( ((GUIContainer*)root->dat)[c] );
		}
		else
		{
			free( ((GUIContainer*)root->dat)[c] );
		}
	}
		
}

// NOW ALL THATS LEFT IS CREATE GUI ELEMENT AND DYNAMICALLY RESIZABLE BUTTONS WHEN CREATION

void FillGUI(GUI* self, Color col)///, Uint8 grad)
{
	SDL_PixelFormat* format = self->surface->format;
	
	Uint32 p = SDL_MapRGB(format, col.r, col.g, col.b); ///Uint32 p[grad] nee malloc;
	
	///for(Uint8 c = 0; c != grad; ++c) p[c] = SDL_MapRGBA(format, col.r + c, col.g + c, col.b + c, col.a + c);
	
	for(int c = 0; c <= self->surface->h * self->surface->w; ++c) *((Uint32*)self->surface->pixels + (c)) = p;

	/// SDL_UpdateWindowSurface(self->window);
}

void UpdateElementGUI(GUI* self, GUIElement* elem, Uint32 x, Uint32 y, Uint16 width, Uint16 height)
{
	///if(elem->type == GUI_INTERACT)	
	
	elem->current = (elem->current + 1) % elem->amount;
	
	for(Uint32 ry = 0; ry != height; ++ry)
	
		for(Uint32 rx = 0; rx != width; ++rx)

			*((Uint32*)self->surface->pixels + ( (x+rx) + ( (y+ry)*self->surface->w))) = ( ((Uint32**)elem->dat)[elem->current] ) + (rx + (ry*width));
			
}		

void PlaceElementGUI(GUI* self, GUIElement* elem, Uint32 x, Uint32 y, Uint16 width)
{
	Uint32*[2] button;
	
	if(elem->type == GUI_INTERACT)
	{
		button[0] = _CreateRectBackgroundGraphic(self->surface->format, 0, width, 16);
		button[1] = _CreateRectBackgroundGraphic(self->surface->format, ~0, width, 16);
	}
	
	*((Uint32*)self->surface->pixels + (x + (y*self->surface->w))) = ///!!!
	

void PlaceGUI(GUI* self, char* txt)	/// Could have been done way more efficient by always checking for 'NUL' and inputting the characters as an index for an array...
{
	Uint32 seek = 0, seekName = 0;										/// Seeking Variables
	
	///Uint32* cseek = &seek;											/// Unused
	
	Uint32 celem = 0;													/// Current Element Offset
	
	char* cname;														/// Current Name
	
	GUIElement* celem;													/// Current GUIElement
	
	
	struct																/// The States:
	{
		/// # Loop Control # /// 	  interpMode is `else`
		
		Uint8 termiMode : 1;											/// Termination Mode
		Uint8 enterMode : 1;											/// Enter Name Mode!
		
		Uint8 exDefMode : 1;											/// Extend Intended Operation/Definition 'Mode'
		
		/// # Sub-States # ///
		
		Uint8 DWS		: 1;											/// Disable WhiteSpace
		
		/// # Mini Data # ///
		
		Uint8 elemType  : 2;											/// Element Type
		
		/// bits remain:  2
		
	} state;
	*((Uint8*)&state) = 0;
	
	
	while(!state.termiMode)
	{
		SDL_Log("Processing character: \'%c\';", txt[seek]);
		if(state.enterMode)
		{	
			switch(txt[seek])											/// Valid Context For 'enterMode' KEK
			{
				
				// # 'enterMode' termanating characters # //
				
				case ';':
				case ':':
				{
					SDL_Log("name (%s) used for property specifier name\n", cname);
					/// Poetisdispencer here propSpec
					
					free(cname);										/// free
					seekName = 0;
					state.enterMode = 0;
					state.DWS = 0;
					break;
				}
				case '\0':
				{
					SDL_Log("GUI in \'enterMode\' done reading GUI configuration txt\n");
					state.termiMode = 1;
					/// musst continue!
				}
				case ']' :
				case '\\':
				case '}' :
				{
					SDL_Log("Ending enterMode");
					
					celem = malloc(sizeof(GUIElement);
					celem->type = state.elemType;
					celem->txt = CreateDataCopy(cname, seekName);
					
					SDL_Log("Result:\n{\n\t name: %s;\n\t type: %b;\n}\n", cname, state.elemType);
					
					free(cname);										/// free
					seekName = 0;
					
					state.elemType = 0b00;
					state.enterMode = 0;
					break;
				}
				
				
				// # 'enterMode' acceptable characters # //
				
				case '\t':
				case ' ' :
				{
					if(state.DWS) break;								/// don't record characters, if white space isn't allowed
				}
				default:
				{
					cname = realloc(cname, seekName + 1);				/// realloc + NUL terminator
					cname[seekName] = txt[seek];
					++seekName;
					
					break;
				}
			}
		}
		else if(state.exDefMode)
		{
			switch(txt[seek])
			{
				
				case '\0':
				{
					SDL_Log("GUI in \'exDefMode\' done reading GUI configuration txt\n");
					state.termiMode = 1;
					break;
				}
				
				
				// # 'exDefMode' valid characters # //
				
				
				case '>':												/// -> (:
				{
					SDL_Log("property specifier = selector ->\n");
					/// Set PropSpec
				}
				
				default:
				{
					state.DWS = 1;
					
					state.exDefMode = 0;
					cname = malloc(1);									/// malloc + NUL char
					state.enterMode = 1;
					break;
				}
			}
		}
		else
		{
			// # 'interpMode' update process # //
			
			
			
			// # 'interpMode' termination # //
			
			switch(txt[seek])
			{
				case '[':
				{
					SDL_Log("elemType = Button");
					state.elemType = 0b10;
					
					cname = malloc(1);									/// malloc + NUL char
					state.enterMode = 1;
					break;
				}
				
				case '/':
				{
					SDL_Log("elemType = TextHeader");
					state.elemType = 0b01;
					
					cname = malloc(1);									/// malloc + NUL char
					state.enterMode = 1;
					break;
				}
				
				
				case '-':
				{
					SDL_Log("GUI property specifier expected ...");
					state.exDefMode = 1;
					break;
				}
				
				
				
				case '\0':
				{
					SDL_Log("GUI done reading GUI configuration txt");
					state.termiMode = 1;
					break;
				}
					
			}
		}
		
		++seek;
	}
}

void UpdateGUI(GUI* self)
{
	///
}


/*

VStack
{
	HStack {	Text"-->", Button, Text"<--"	}
	
	HStack {		Button, Text"Close"			}
	
}
**/
