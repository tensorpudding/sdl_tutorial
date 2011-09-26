#include "CApp.h"

CApp::CApp() {
    CurrentPlayer = 0;

    Surf_Grid = NULL;
    Surf_X = NULL;
    Surf_O = NULL;

    Surf_Display = NULL;

    Running = true;
}

int CApp::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }

    SDL_Event Event;
    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }
    OnCleanup();

    return 0;
}

bool CApp::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((Surf_Display =
         SDL_SetVideoMode(600, 600, 32,
                          SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    if ((Surf_Grid = CSurface::OnLoad("./grid.bmp")) == NULL) {
        return false;
    }
    
    if ((Surf_X = CSurface::OnLoad("./x.bmp")) == NULL) {
        return false;
    }

    if ((Surf_O = CSurface::OnLoad("./o.bmp")) == NULL) {
        return false;
    }
    CSurface::Transparent(Surf_X, 255, 0, 255);
    CSurface::Transparent(Surf_O, 255, 0, 255);

    // Reset grid
    Reset();

    return true;
}

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnLButtonDown(int mX, int mY) {
    int ID = mX / 200;
    ID = ID + ((mY / 200) * 3);

    if (Grid[ID] != GRID_TYPE_NONE) {
        return;
    }

    if (CurrentPlayer == 0) {
        SetCell(ID, GRID_TYPE_X);
        CurrentPlayer = 1;
    } else {
        SetCell(ID, GRID_TYPE_O);
        CurrentPlayer = 0;
    }
}

void CApp::OnExit() {
    Running = false;
} 


void CApp::OnLoop() {
}

void CApp::OnRender() {
    CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);   

    for (int i = 0; i < 9; i++) {
        int X = (i % 3) * 200;
        int Y = (i / 3) * 200;

        if (Grid[i] == GRID_TYPE_X) {
            CSurface::OnDraw(Surf_Display, Surf_X, X, Y);
        }
        else if (Grid[i] == GRID_TYPE_O) {
            CSurface::OnDraw(Surf_Display, Surf_O, X, Y);
        }
    }

    SDL_Flip(Surf_Display);
}

void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Grid);
    SDL_FreeSurface(Surf_X);
    SDL_FreeSurface(Surf_O);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

void CApp::Reset() {
    for (int i = 0; i < 9; i++) {
        Grid[i] = GRID_TYPE_NONE;
    }
}

void CApp::SetCell(int ID, int Type) {
    if (ID < 0 || ID >= 9) return;
    if (Type < 0 || Type > GRID_TYPE_O) return;
    Grid[ID] = Type;
}
