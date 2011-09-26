#ifndef _CAPP_H
#define _CAPP_H

#include <SDL.h>
#include "CSurface.h"
#include "CEvent.h"

class CApp : public CEvent {

private:
    bool         Running;

    SDL_Surface* Surf_Display;

    SDL_Surface* Surf_Grid;

    SDL_Surface* Surf_X;
    SDL_Surface* Surf_O;

    int Grid[9];

    enum {
      GRID_TYPE_NONE = 0,
      GRID_TYPE_X,
      GRID_TYPE_O
    };

    int CurrentPlayer;

public:

    CApp();

    int OnExecute();

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLButtonDown(int mX, int mY);

    void OnExit();

    void OnLoop();

    void OnRender();

    void OnCleanup();

    void Reset();

    void SetCell(int ID, int Type);

};

#endif
