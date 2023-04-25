#include "menu.h"

menu::menu(){

    buttonBox[0] = {(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT};
    for(int i = 0; i < TOTAl_BUTTON, i++){
        buttonClip[i][0] = {0, 1696, 368, 176};
        buttonClip[i][1] = {368, 1296, 368, 176};
        mouseOver[i] = 0;
    }

}


void menu::handle(SDL_Event &e){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
        for(int i = 0; i < TOTAl_BUTTON; i++){
            mouseOver[i] = 0;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < TOTAl_BUTTON; i++){
            bool inside = 0;
            if(buttonBox[0].x < x && x < buttonBox[0].x + BUTTON_WIDTH && buttonBox.y < y && y < buttonBox + BUTTON_HEIGHT){
                inside = 1;
            }
            if(inside){
                switch(e.type){
                    case SDL_MOUSEBUTTONDOWN:

                    break;
                    case SDL_MOUSEMOTION:
                        mouseOver[i] = 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void menu::render(createWindow mWindow, SDL_Texture* mTexture[]){

}

reload::reload(){
    posX = (SCREEN_WIDTH - RESTART_GAME_WIDTH) / 2;
    posY = (SCREEN_HEIGHT - RESTART_GAME_HEIGHT) / 2;
    restartClip = {0, 0, 960, 880};
    restart = false;
}

void reload::handle(SDL_Event &e){
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

void reload::render(createWindow mWindow, SDL_Texture* mTexture[]){
    mWindow.render(mTexture[MENU_TEXTURE], posX, posY, &restartClip, 0, NULL, SDL_FLIP_NONE, RESTART_GAME_WIDTH, RESTART_GAME_HEIGHT*11/12);

}

bool reload::getRestart(){
    return restart;
}
