#ifndef MENU_H
#define MENU_H

#include "base.h"

class menu{
public:
    menu();

    void handle(SDL_Event &e);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);

private:
//    int PLAY = 0;
//    int QUIT = 1;
//    int TOTAL_BUTTON = 2;
//    SDL_Rect buttonClip[TOTAL_BUTTON];
//    SDL_Rect button[TOTAL_BUTTON];



};

class reload{
public:
    reload();

    void handle(SDL_Event &e);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);
    bool getRestart();
private:
    int posX, posY;
    SDL_Rect restartClip;
    bool restart;
};

#endif // MENU_H
