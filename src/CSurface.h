#ifndef _CSURFACE_H
#define _CSURFACE_H

#include <SDL.h>

class CSurface {
public:
    CSurface();

    static SDL_Surface* OnLoad(char* File);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src,
                       int X, int Y);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src,
                       int X1, int Y1, int X2, int Y2, int W, int H);

    static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};

#endif
