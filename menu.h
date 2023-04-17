#ifndef MENU_H
#define MENU_H

#include "base.h"

class menu{
public:
    menu();

    void handle(SDL_Event &e);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);
    bool getRestart();
private:
    int posX, posY;
    SDL_Rect restartClip;
    bool restart;
};

#endif // MENU_H
