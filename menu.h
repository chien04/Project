#ifndef MENU_H
#define MENU_H

#include "base.h"

class menu{
public:
    menu();

    void handle(SDL_Event &e, int &stateMenu, Mix_Chunk *gameSound[]);
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

    void handle(SDL_Event &e, int& stateReload, Mix_Chunk *gameSound[]);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);
    bool getRestart();
private:
    enum again{
        RELOAD,
        MENU,
        TOTAL_BUTTONRELOAD
    };
    SDL_Rect backgroundClip;
    SDL_Rect buttonBox[TOTAL_BUTTONRELOAD];
    SDL_Rect buttonClip[TOTAL_BUTTONRELOAD][2];
    bool mouseOver[TOTAL_BUTTONRELOAD];
    bool restart;
};

class pause{
public:
    pause();
    void handle(SDL_Event &e, int& statePause, Mix_Chunk *gameSound[]);
    void render(createWindow mWindow, SDL_Texture* mTexture[]);
private:
    enum pauseGame{
        RESTART,
        MENU,
        CONTINUTE,
        TOTAL_BUTTONPAUSE
    };
    SDL_Rect backgroundClip;
    SDL_Rect buttonBox[TOTAL_BUTTONPAUSE];
    SDL_Rect buttonClip[TOTAL_BUTTONPAUSE][2];
    bool mouseOver[TOTAL_BUTTONPAUSE];
};

class won{
public:
    won();
    void handle(SDL_Event &e, int& statesWon, Mix_Chunk *gameSound[]);
    void render(createWindow mWindow, SDL_Texture *mTexture[]);

private:
    enum winGame{
        RESTART,
        MENU,
        TOTAL_BUTTONWIN
    };
    SDL_Rect backgroundClip;
    SDL_Rect buttonBox[TOTAL_BUTTONWIN];
    SDL_Rect buttonClip[TOTAL_BUTTONWIN][2];
    bool mouseOver[TOTAL_BUTTONWIN];

};

class guide{
public:
    guide();
    void handle(SDL_Event &e, int& statesGuide, Mix_Chunk *gameSound[]);
    void render(createWindow mWindow, SDL_Texture *mTexture[]);

private:
    enum winGame{
        MENU,
        TOTAL_BUTTON
    };
    SDL_Rect buttonBox[TOTAL_BUTTON];
    SDL_Rect buttonClip[TOTAL_BUTTON][2];
    bool mouseOver[TOTAL_BUTTON];

};
#endif // MENU_H
