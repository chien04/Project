#include "menu.h"

menu::menu(){
    posX = (SCREEN_WIDTH - RESTART_GAME_WIDTH) / 2;
    posY = (SCREEN_HEIGHT - RESTART_GAME_HEIGHT) / 2;
    restartClip = {0, 0, 960, 880};
    restart = false;
}

void menu::handle(SDL_Event &e){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        int posX, posY;
        SDL_GetMouseState(&posX, &posY);
        bool inSide = false;
        if(posX > 495 && posX < 585){
            if(posY > 375 && posY < 450){
                inSide = true;
            }
        }
        if(inSide){
            switch(e.type){
                case SDL_MOUSEBUTTONDOWN:
                    restart = true;
                    break;
            }
        }
    }
}

void menu::render(createWindow mWindow, SDL_Texture* mTexture[]){
    mWindow.render(mTexture[MENU_TEXTURE], posX, posY, &restartClip, 0, NULL, SDL_FLIP_NONE, RESTART_GAME_WIDTH, RESTART_GAME_HEIGHT*11/12);

}

bool menu::getRestart(){
    return restart;
}
