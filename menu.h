#ifndef MENU_H
#define MENU_H

#include "base.h"

class menu{
public:
    menu();

    void handle(SDL_Event &e, int &state);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);

private:
    enum menuButton{
        PLAY,
        GUIDE,
        QUIT,
        TOTAL_BUTTON
    };
    SDL_Rect backgroundClip;
    SDL_Rect buttonBox[TOTAL_BUTTON];
//    SDL_Rect button[TOTAL_BUTTON];
    SDL_Rect buttonClip[TOTAL_BUTTON][2];
    bool mouseOver[TOTAL_BUTTON];



};

class reload{
public:
    reload();

    void handle(SDL_Event &e);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);
    bool getRestart();
private:
    enum again{
        RELOAD,
        MENU,
        TOTAL_BUTTON
    };
    SDL_Rect backgroundClip;
    SDL_Rect buttonBox[TOTAL_BUTTON];
    SDL_Rect buttonClip[TOTAL_BUTTON][2];
    bool mouseOver[TOTAL_BUTTON];
    bool restart;
};

#endif // MENU_H
