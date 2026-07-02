#include "../basics.h"
// ############### //
// # Definitions # //

typedef struct
{
	char* name;
	void* data;
	
} Property;

typedef struct
{
	char* name;
	void* func;
	Uint16 paramAmount;
	
} Method;

typedef struct
{
	char* name;
	
	void* create;
	void* destroy;

	Uint16 paramAmount;
	
	struct
	{
		Uint8 special : 1;
		
	} flags;
	
} Module;

// # External Functions # //

///extern 
