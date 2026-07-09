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


#define _BG_AG_0  ((Uint8) 0x39 )	/// Additionals Frame 0
#define _BG_AG_1  ((Uint8) 0x52 )	/// Additionals Frame 1

#define _BG_AG_LENGTH  ((Uint8) 15 )	/// Additionals Length


/**Pixels _UnpackBackgroundGraphic(SDL_PixelFormat* format, Uint16 side, Uint16 size) /// ALL ( ~0 ) or NOTHING ( 0 )		/// MUST BE UNSIGNED
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

}*/

Pixels _CreateRectBackgroundGraphic(SDL_PixelFormat* format, Uint16 side, Uint16 width, Uint16 height) /// ALL ( ~0 ) or NOTHING ( 0 )		/// MUST BE UNSIGNED
{
	Uint32 AC = ((Uint8[2]){_BG_AG_0, _BG_AG_1})[!! side]; //Uint16 tot = _BG_HEIGHT * _BG_WIDTH;
	
	Uint32* buf = malloc(sizeof(Uint32) * width * height);
	
	buf[0] = SDL_MapRGB(format, _BG_BGL, _BG_BGL, _BG_BGL); AC = SDL_MapRGB(format, AC, AC, AC);
	
	Sint8 add = !side - !!side;
	
	for(Uint16 c = 1; c != width * height; ++c)
		buf[c] = buf[0];
	
	///SDL_Log(" Uint8 x = %i; x != %i; x += %i ", (width-1) & (side), (width) & (~side), (Sint8) !side - !!side );
	for( Sint16 x = ( (width-1) & side ); x != ( (width-1) & (~side) ); x += add )
	
		buf[ x + ( width * (height-1) & side ) ] = AC;
		
	for( Sint16 y = ( (height-1) & side ); y != ( (height-1) & (~side) ); y += add )
	
		buf[ ( (width-1) & side) + width * y ] = AC;
	
	return buf;
}
