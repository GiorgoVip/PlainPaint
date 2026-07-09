#include "../basics.h"

typedef struct
{
	// # Properties # //
	
	SDL_Color color;
	
	Uint32 size;
	/**struct
	{
		Uint8 init : 1;
		Uint8 dead : 1;
		Uint8 busy : 1;
		
	} status;*/
	char* name;
	
}Equipment;
	
// # Global Properties # /

enum Equipments
{
	EQP_NORMAL_BRUSH = 0,
	
	EQP_ERASER = 1,
	
	EQP_UNKNOWN = 2
};

#define EQP_AMOUNT 3
Equipment EquipmentList[EQP_AMOUNT] =									/// Best to eventually make this into a registry
{
	(Equipment)// NormalBrush
	{
		(SDL_Color){0, 0, 0, 255},
		
		5,
		
		"NORMAL_BRUSH"
	},
	
	
	(Equipment)// Eraser
	{
		(SDL_Color){},
		
		5,
		
		"ERASER"
	},
	
	
	(Equipment)// Unknown
	{
		(SDL_Color){0, 0, 0, 90},
		
		10,
		
		"UNKNOWN"
	},
};

Equipment* CurrentEquipment = EquipmentList;

// # Methods # //

///Equipment* CreateEquipment();

///void DestroyEquipment(Equipment* self);





