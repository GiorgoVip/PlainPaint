#include "../Resources/internal.h"

// # Structures # //

typedef struct
{
	SDL_Surface* gfx;
	
	Uint32 unitSlice;
	
	/// Potential OP choice	'=', '|=', '&=' ?
	
} GUIFont;

#define GUI_CONTAINS_GRAPHICS 0b001
#define GUI_UPDATE_NOT_NEEDED 0b010
#define GUI_IS_INTERACTABLE   0b100

typedef enum
{
	///							ICG										
	
	GUI_STATIC 				= 0b011,									/// Images etc
	GUI_STATIC_TEXT 		= 0b010,									/// Texts
	GUI_STATIC_STREAM 		= 0b001,									/// Streamed Images etc
	
	GUI_INTERACT 			= 0b111,									/// Button etc
	GUI_INTERACT_PERMA 		= 0b101,									/// Checkbox etc
	GUI_INTERACT_LISTENER 	= 0b100,									/// Regular inp/evn Triggers
	
	GUI_CONTAINER 			= 0b000,									/// Container for elements

} GUIElementType;

typedef struct { char key; int val; } GUIProperties; /// void* instead of int to have true variables /// GUIElement could have had (GUIContainer) Origin, check with for loop until NUL when cleanong

typedef struct
{
	GUIElementType  type;
	GUIProperties* props;
	
	char* txt;															/// Could also be used for misc. data, IDs
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
	
// # Static Properties # /


static GUIFont DefaultFont;

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
	
	
	DefaultFont = (GUIFont){ SDL_ConvertSurface(SDL_LoadBMP("./DefaultFont.bmp"), self->surface->format, 0), _FONT_WIDTH }; /// LoadDefaultFont Graphic BMP
	
	SDL_Log("Initialized GUI successfully");
	
	return self;
}

void DestroyGUI(GUI* self)
{
	///
	
	SDL_FreeSurface(DefaultFont.gfx);
	
	self->status.dead = 1;
	free(self->root);													/// Yezzz Cleaner doesn't free the root
	free(self);
}

GUIElement* CreateGUIElement(GUI* gui, GUIElementType type, char* txt)	/// Please CreateElementGUI instead
{
	GUIElement* self = malloc(sizeof(GUIElement));
	
	self->type = type;
	
	if(type == GUI_INTERACT)
	{
		/// dat is a Pointer to a List that contains Pointers to misc. data!
		
		self->amount = 2; self->dat = malloc(sizeof(Pixels*) * self->amount); ///Pixels px = malloc(sizeof(Uint32) * 32 * 16); for(Uint32 c = 0; c != 32 * 16; ++c) px[c] = 0x00ffff;
		( (Pixels*)self->dat)[0] = _CreateRectBackgroundGraphic(gui->surface->format, ~0, 128, 16);
		( (Pixels*)self->dat)[1] = _CreateRectBackgroundGraphic(gui->surface->format, 0, 128, 16);
	}
	self->txt = txt;
	return self;
}

GUIElement* CreateElementGUI(GUI* self, GUIContainer* root, GUIElementType type, char* id)
{
	root->dat = realloc(root->dat, (root->amount+1) * sizeof(GUIElement*));
	
	GUIElement* elem = CreateGUIElement(self, type, id);
	
	( (GUIElement**)root->dat )[root->amount] = elem;
	
	++root->amount;
	
	return elem;
}

///void DestroyGUIElement(GUIElement* self)


int GetPropertyGUIElement(GUIElement* elem, char key)
{
	for(unsigned int c = 1; c <= elem->props[0].val; ++c)///for(unsigned int c = 1; c != *(unsigned int*)(elem->props[0].val); ++c)
	{
		if(elem->props[c].key == key)	{ return elem->props[c].val; }
	}
	
	return -1;
}

void SetPropertyGUIElement(GUIElement* elem, char key, void* value)
{
	for(unsigned int c = 1; c <= elem->props[0].val; ++c)
	{
		if(elem->props[c].key == key)	{ elem->props[c].val = value; break; }
	}
}

void ListoutPropertiesGUIElement(GUIElement* elem)
{
	for(unsigned int c = 1; c <= elem->props[0].val; ++c)
	{
		SDL_Log("Property Key: \'%c\'; Value: %i.", elem->props[c].key, elem->props[c].val);
	}
}

void CleanGUIContainer(GUIContainer* root)
{
	SDL_Log("GUI Cleaning %s\n", root->txt);
	
	GUIContainer* ptr;
	
	for(Uint32 c = 0; c != root->amount; ++c)
	{
		ptr = ( (GUIContainer**)root->dat )[c];							/// Points to the current sub-element
		
		if( ptr->type == GUI_CONTAINER )
		{
			CleanGUIContainer( ptr );
		}
		else
		{	if( ptr->type != GUI_INTERACT ) { // TMP!!!
			for(Uint32 cr = 0; cr != ptr->amount; ++cr)					/// Free up any resources if any
			{	
				free( ((Pixels*)ptr->dat)[cr] );						/// Just needs to be a Pointer to Data Pointers
			}
			
			free( ptr->dat ); }
		}
		
		if( ptr->props )												/// props counter (not counting itself), we must take loopcheck way
		{			
			free( ptr->props );
		}
		
		free( ptr->txt );
		
		free( ptr );													///	Always get rid of the sub-element wether container or not
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

void PlaceTextGUI(GUI* self, GUIFont* font, Uint32 x, Uint32 y, Uint32 scale, char* txt)
{
	if(!font) font = &DefaultFont;
	
	for(Uint32 seek = 0; txt[seek] >= ' '; ++seek)
	{
		Uint32 base = font->unitSlice * ( txt[seek] - ' ' );
		
		///SDL_Log("Going forward xc = %i, txt[seek] = %i, unitSlize = %i", font->unitSlice * ( txt[seek] - ' ' ), txt[seek], font->unitSlice);
		for(Uint16 xc = 0; xc != font->unitSlice * scale; ++xc)
		{
			for(Uint16 yc = 0; yc != font->gfx->h * scale; ++yc)
			{	
				*((Uint32*)self->surface->pixels + ((xc+x) + ((yc+y)*self->surface->w))) |= *(  (Uint32*)font->gfx->pixels + base + ( xc / scale + (yc / scale * font->gfx->w) )  );
			}
		}
		
		x += font->unitSlice * scale;
	}
	
	SDL_UpdateWindowSurface(self->surface);
}

void PlaceElementGraphicGUI(GUI* self, GUIElement* elem, Uint32 x, Uint32 y, Uint16 width, Uint16 height, Uint8 inc)
{
	if( elem->dat )	/// NUL : NOTHING
	{
		elem->current = (elem->current + inc) % elem->amount;

		for(Uint32 ry = 0; ry != height; ++ry)
	
			for(Uint32 rx = 0; rx != width; ++rx)

				*((Uint32*)self->surface->pixels + ( (x+rx) + ( (y+ry)*self->surface->w))) = *(  *( (Uint32**)elem->dat + elem->current ) + (rx + (ry*width))  );
	}
}

void UpdateElementsGUI(GUI* self, GUIContainer* root, Uint8 inc)
{
	///SDL_Log("GUI Updating %s GUIContainer\n", root->txt);
	
	GUIContainer* ptr;
	
	for(Uint32 c = 0; c != root->amount; ++c)
	{
		ptr = ( (GUIContainer**)root->dat )[c];							/// Points to the current sub-element
		
		if( ptr->type & GUI_CONTAINS_GRAPHICS )							/// type == 0b??1
				PlaceElementGraphicGUI(self, ptr, 10, c*17 + 10, 128, 16, inc);
		
		if( ptr->txt )													///// Cannot suffice! Containers shouldn'ty display txt
			PlaceTextGUI(self, 0/**(GUIFont*)ptr->dat*/, 14, c*17 + 14, 1, ptr->txt);///// Button has graphics in dat but also needs FONT pls fix
		
		switch( ptr->type )												
		{
			case GUI_CONTAINER:
			{
				UpdateElementsGUI(self, ptr, inc);
				break;
			}
			
			/**case GUI_STATIC_TEXT:
			{
				PlaceTextGUI(self, (GUIFont*)ptr->dat, 50, 50, 1, ptr->txt);
				break;
			}*/
		}

		
		///*((Uint32*)self->surface->pixels + ( (50) + ( (50)*self->surface->w))) = 0xff00ff;
	}
}

void WipeElementGUI(GUI* self, GUIElement* elem)
{
	///
}


void PlaceGUI(GUI* self, char* txt)	/// Could have been done way more efficient by always checking for 'NUL' and inputting the characters as an index for an array...
{
	Uint32 seek = 0, seekName = 0;										/// Seeking Variables
	
	unsigned int* cprop;												/// Property Counter
	
	GUIElement* celem;										    		/// Current Element
	
	char* cname;														/// Current Name
	
	GUIContainer* ccont = self->root;									/// Current GUIContainer
	
	
	struct																/// The States:
	{
		/// # Loop Control # /// 	  interpMode is `else`
		
		Uint8 termiMode : 1;											/// Termination Mode
		Uint8 enterMode : 1;											/// Enter Name Mode!
		
		Uint8 exDefMode : 1;											/// Extend Intended Operation/Definition 'Mode'
		
		/// # Sub-States # ///
		
		Uint8 DWS		: 1;											/// Disable WhiteSpace
		
		/// # Mini Data # ///
		
		Uint8 elemType  : 3;											/// Element Type
		
		/// bits remain:  1
		
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
				{
					celem->props[*cprop].val = ConvertStringToInteger(cname);
					
					SDL_Log("cprops: %i, key: %c, val: %i.", *cprop, celem->props[*cprop].key, celem->props[*cprop].val);
				}
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
					
					celem = CreateElementGUI(self, ccont, state.elemType, CreateDataCopy(cname, seekName));	/// Create and Register a new element
					
					/// # Properties Initialization stuff # ///
					celem->props = malloc(sizeof(GUIProperties));		/// malloc list with 1 element
					cprop = &celem->props[0].val; *cprop = 0;
					
					SDL_Log("Result:\n{\n\t name: %s;\n\t type: %b;\n}\n", cname, state.elemType);
					
					free(cname);										/// free for reuse
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
					/// Must convert cname into ID on ; instead of str->num
				}
				
				default:
				{
					state.DWS = 1;
					
					state.exDefMode = 0;
					cname = malloc(1);									/// malloc + NUL char
					state.enterMode = 1;
					
					/// # Properties stuff # ///
					++(*cprop);
					celem->props = realloc(celem->props, ((*cprop)+1) * sizeof(GUIProperties)); /// realloc can verhuis /// Counter Property only keeps track of other props, therefor +1 because it is still included and stuff
					cprop = &celem->props[0].val; celem->props[*cprop].key = txt[seek];
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
					state.elemType = GUI_INTERACT;
					
					cname = malloc(1);									/// malloc + NUL char
					state.enterMode = 1;
					break;
				}
				
				case '/':
				{
					SDL_Log("elemType = TextHeader");
					state.elemType = GUI_STATIC_TEXT;
					
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

void UpdateButtonGUI(GUI* self, Point2D point, Uint8 set, Canvas* canvas, Uint8 nee)
{
	GUIContainer* ptr;
	
	for(Uint32 c = 0; c != self->root->amount; ++c)
	{
		ptr = ( (GUIContainer**)self->root->dat )[c];							/// Points to the current sub-element
			
		if( point.x >= 10 && point.x <= (10 + 128)   &&   point.y >= (10 + c*17) && point.y <= (10 + c*17 + 16) )
		{
			///SDL_Log("HAP SAP APPELSAP%i", c);
				
			ptr->current = set;
				
			if( ptr->type == GUI_INTERACT )
			{
				PlaceElementGraphicGUI(self, ptr, 10, c*17 + 10, 128, 16,  0);
			
				if( ptr->txt )
					PlaceTextGUI(self, 0/**(GUIFont*)ptr->dat*/, (14+set), c*17 + (14+set), 1, ptr->txt);
				
				if(set)
				{
					int eqp = GetPropertyGUIElement(ptr, '>');
					
					if(eqp != -1) CurrentEquipment = EquipmentList + eqp;
					
					
					eqp = GetPropertyGUIElement(ptr, '<');
					
					switch( eqp )
					{
						case 0:
						{
							SaveCanvas(canvas);
							
							break;
						}
						
						case 1:
						{
							LoadCanvas(canvas);
							
							break;
						}
					}
				}
			}
		}
			
	}
}


void UpdateGUI(GUI* self, Canvas* canvas )												/// Lookat else its better to just call when needed instead of constantly
{
	int mx, my;
	
	if(barFocus)
	{
		if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT))

			UpdateButtonGUI(self, (Point2D){mx, my}, 1, canvas, 0);

	
		else

			UpdateButtonGUI(self, (Point2D){mx, my}, 0, canvas, 0);
			
	}
}


/*

VStack
{
	HStack {	Text"-->", Button, Text"<--"	}
	
	HStack {		Button, Text"Close"			}
	
}
**/


// # Equipment Leftovers # ///


void PlaceEquipmentButtons(GUI* self)
{
	GUIElement* celem; char* aname;										/// Always free's the txt attribute
	
	for(Uint32 c = 0; c != EQP_AMOUNT; ++c)
	{
		aname = CreateStringCopy(EquipmentList[c].name);
		
		celem = CreateElementGUI(self, self->root, GUI_INTERACT, aname);
		
		celem->props = malloc(sizeof(GUIProperties) * 2);
		celem->props[1].key = '>';
		celem->props[1].val = c;
		
		celem->props[0].val = 1;										/// Doesn't Count itself
	}
}

