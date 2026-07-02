#include "./iconz.h"

// # Executable Internal Graphics # //


// # Background Graphic # //

#define _BG_WIDTH  ((Uint8) 16 )
#define _BG_HEIGHT  _BG_WIDTH

/*const SDL_Color _BG_GRAPHIC[_BG_WIDTH * _BG_HEIGHT] =
{
	///
};*/

#define _BG_BGL  ((Uint8) 0xA5 )	/// Background Lightness


#define _BG_AG_0  ((Uint8) 0x00 )	/// Additionals Frame 0
#define _BG_AG_1  ((Uint8) 0x00 )	/// Additionals Frame 1

#define _BG_AG_LENGTH  ((Uint8) 15 )	/// Additionals Length


Uint32* _UnpackBackgroundGraphic(SDL_PixelFormat* format, Uint16 side, Uint16 size) /// ALL ( ~0 ) or NOTHING ( 0 )		/// MUST BE UNSIGNED
{
	Uint32 AC = ((Uint8[2]){_BG_AG_0, _BG_AG_1})[!! side]; //Uint16 tot = _BG_HEIGHT * _BG_WIDTH;
	
	Uint32 buf[size * size];
	
	buf[0] = SDL_MapRGB(format, _BG_BGL, _BG_BGL, _BG_BGL); AC = SDL_MapRGB(format, AC, AC, AC);
	
	Uint16 adsize = size - 1;
	
	for(Uint16 c = 1; c != size * size; ++c)
		buf[c] = buf[0];
	
	
	for( Uint8 c = (side & size) - (!! side); c != ((~side) & adsize); c += (Sint8) !side - !!side ) ///( !!( side & 0b00000011 ) ) * tot
	{
		buf[c + size * (side & adsize) ] = AC;	buf[c * size + (side & adsize)] = AC;
	}
	return buf;

}

Uint32* _CreateRectBackgroundGraphic(SDL_PixelFormat* format, Uint16 side, Uint16 width, Uint16 height) /// ALL ( ~0 ) or NOTHING ( 0 )		/// MUST BE UNSIGNED
{
	Uint32 AC = ((Uint8[2]){_BG_AG_0, _BG_AG_1})[!! side]; //Uint16 tot = _BG_HEIGHT * _BG_WIDTH;
	
	Uint32 buf = malloc(width * height);
	
	buf[0] = SDL_MapRGB(format, _BG_BGL, _BG_BGL, _BG_BGL); AC = SDL_MapRGB(format, AC, AC, AC);
	
	///Uint16 adsize = size - 1;
	
	for(Uint16 c = 1; c != width * height; ++c)
		buf[c] = buf[0];
	
	
	for( Uint16 y = (side & height) - (!! side); y != ((~side) & (height-1)); y += (Sint8) !side - !!side)
	{
		buf[y * height + (side & (height-1))] = AC;
	}
	
	for( Uint16 x = (side & width) - (!! side); x != ((~side) & (width-1)); x += (Sint8) !side - !!side)
	{
		buf[x + width * (side & (width-1))] = AC;
	}
	
	return buf;
}
