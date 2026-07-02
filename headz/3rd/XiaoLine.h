#include "../../basics.h"

// my Implmentation for Xiaolin Wu's Anti-aliasing Line Drawing Algorithm			https://web.archive.org/web/20170325025628/https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm



int XiaoRound(float n)
{
	return (int)(n + 0.5);
}

float XiaoFpart(float n)
{
	if(n < 0)
		return 1 - (n - SDL_floor(n));
	
	return n - SDL_floor(n);
}

float XiaoRfpart(float n)
{
	return 1 - XiaoFpart(n);
}


void XiaoPlotL(SDL_Surface* sur, int x, int y, Uint8 l)
{
	//Uint32 px = (l << 8*3) | (l << 8*2) | (l << 8*1) | (l << 8*0);
	
	Uint32 px = (l << 16) | (l << 8) | (l); //(l << 24) | (l << 16) | (l << 8) | (0xff);
	
	*((Uint32*)sur->pixels + (x + (y*sur->w))) = px;
}

void XiaoPlotC(SDL_Surface* sur, int x, int y, Uint32 px)
{
	//Uint32 px = (l << 8*3) | (l << 8*2) | (l << 8*1) | (l << 8*0);
	
	//Uint32 px = (l << 24) | (l << 16) | (l << 8) | (0xff);
	
	*((Uint32*)sur->pixels + (x + (y*sur->w))) = px;
}


/*void XiaoLine(SDL_Surface* sur, float xs, float ys, float xd, float yd)
{
	float s;
	bool steep = SDL_abs( yd - ys ) > SDL_abs( xd - xs );
	
	if(steep)
	{
		s = xs; xs = ys; ys = s;
		s = xd; xd = yd; yd = s;
	}
	if(xs > xd)
	{
		s = xs; xs = xd; xd = s;
		s = ys; ys = yd; yd = s;
	}
	
	float dx = xd - xs;
	float dy = yd - ys;
	float g = dy / dx;
	if(dx == 0.0)
		g = 1.0;
	
	float xe = XiaoRound(xs);
	float ye = ys + g * (xe - xs);
	float xgap = XiaoRfpart(xs + 0.5);
	float xpx1 = xe;
	float ypx1 = (int)ye;

	if(steep)
	{
        XiaoPlotL(ypxl1,   xpxl1, rfpart(yend) * xgap)
        XiaoPlotL(ypxl1+1, xpxl1,  fpart(yend) * xgap)
    }
    else
    {
        XiaoPlotL(xpxl1, ypxl1  , rfpart(yend) * xgap)
        XiaoPlotL(xpxl1, ypxl1+1,  fpart(yend) * xgap)
    }
    float intery = ye + g;

*/
