#include "../basics.h"

// # extra essential stuff # //



// # FUNCTIONS # //

// # Number # //
Sint8 GetSignNumber(Sint32 num)
{
	return (num < 0) ? -1 : (num > 0) ? 1 : 0;
}

// # Color # //
/*Uint32 SplitColor(Uint32 col)
{
	return 0;
}*/

// # Basic Templates # //

typedef struct
{
	// # Properties # //
	Uint32 x, y;
	
} Point;

typedef struct
{
	// # Properties # //
	Uint32 x, y, z;
	
} Point3D;

typedef Point Point2D;

typedef Point2D Vector2;

typedef Point3D Vector3;

/**typedef struct
{
	// # Properties # //
	Uint8 r, g, b, a;
	/// void* Operators;
	
} Color;*/

typedef SDL_Color Color;

double PytoLength(double x1, double y1, double x2, double y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	
	return SDL_sqrt((double) ( dx * dx + dy * dy ));
}


// # DynamicArray Type # //

typedef struct
{
	Uint8 unitSize;
	Uint32 amount;
	
	void* data;
} DynamicArray;

DynamicArray* CreateDynamicArray(Uint32 amount, Uint8 unitSize)
{
	DynamicArray* self = malloc(sizeof(DynamicArray));
	
	self->data = malloc(unitSize); ///(amount * unitSize);
	
	self->unitSize = unitSize;
	self->amount = 0; ///amount;										/// Amount always 0
	return self;
}


void DestroyDynamicArray(DynamicArray* self)
{
	free(self->data);
	
	free(self);
}


void* PushInDynamicArray(DynamicArray* self, void* data)						/// NOT checking MAX size!!!	/// DOES NOT COPY THE POINTER, IT COPIES THE DATA THAT IS BEING POINTED TO!!!
{	
	self->data = realloc(self->data, (self->amount+1) * self->unitSize);	/// plop in data byte per byte *data
	
	for(Uint8 c = 0; c != self->unitSize; ++c)
	{
		((Uint8*)self->data)[self->amount * self->unitSize + c] = ((Uint8*)data)[c];
		
		SDL_Log("trans data: %x \n", ((Uint8*)data)[c]);
	}
	++self->amount;
	
	return self->data;
}

void PopOutDynamicArray(DynamicArray* self)								/// NOT checking if  0   !!!
{
	if(self->amount <= 0)
	{	SDL_Log("DynamicArray is empty!"); return;	}
		
	--self->amount;
	
	self->data = realloc(self->data, self->amount * self->unitSize);
	
	/// return ...
}


// # DynamicString Type # //

typedef struct
{
	Uint32 length;
	
	char* data;
	
} DynamicString;

DynamicString* CreateDynamicString()///Uint32 length)
{
	DynamicString* self = malloc(sizeof(DynamicString));
	
	self->data = malloc(1); self->data[0] = 0;
	
	self->length = 0;///length;
	return self;
}


void DestroyDynamicString(DynamicString* self)
{
	free(self->data);
	
	free(self);
}

void AppendCharDynamicString(DynamicString* self, char character)
{
	++self->length;
	self->data = realloc(self->data, self->length + 1);
	
	self->data[self->length] = character;
	self->data[self->length + 1] = 0;
}


Uint8* CreateDataCopy(Uint8* data, size_t size)
{
	Uint8* rdata = malloc(size);
	
	for(Uint8 c = 0; c != size; ++c)
	{
		rdata[c] = data[c];
	}
	
	return rdata;
}

Uint8* CreateStringCopy(char* str)
{
	char* rstring = malloc(1);
	
	for(Uint8 c = 0; str[c] != '\0'; ++c)
	{
		rstring = realloc(rstring, c+1);
		rstring[c] = str[c];
	}
	
	return rstring;
}

void* dmalloc(size_t bsize, char* ime)
{
	SDL_Log("Allocating Memory for \'%s\' with %i bytes", ime, bsize);
	
	return malloc(bsize);
}

void dfree(void* ptr, char* ime)
{
	SDL_Log("Freeing Memory for \'%s\' at %x", ime, ptr);
	
	free(ptr);
}


int ConvertStringToInteger(char* str)
{
	int val = 0, mul = 1, rad = 10;
	int c = 0;

	switch(str[c])
	{
		case '%':
		{
			rad = 2;
		}
			
		case '$':
		{
			rad = 16;
		}
	}
	
	while(str[c] != '\0') ++c;
	
	while(c != 0)
	{
		--c;
		
		val += mul * (str[c] - '0');
		
		mul *= rad;
	}
	
	return val;	///SDL_Log("Value before %s after %i]", str, val); 
}

char* ConvertIntegerToString(int num)									/// must be free'd
{
	///
}
