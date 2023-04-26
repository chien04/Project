#include "menu.h"

menu::menu(){
    for(int i = 0; i < TOTAL_BUTTON; i++){
        buttonBox[i] = {(SCREEN_WIDTH * 3/ 4 - BUTTON_WIDTH / 2), (SCREEN_HEIGHT * (i+1) / 4 - BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT};
    }
    backgroundClip = {1040, 0, 1280, 640};
    int x = 1680;
    for(int i = 0; i < TOTAL_BUTTON; i++){
        buttonClip[i][0] = {0, x, 368, 192};
        buttonClip[i][1] = {464, x, 368, 192};
        mouseOver[i] = 0;
        x += 224;
    }

}


void menu::handle(SDL_Event &e, int &state){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
        for(int i = 0; i < TOTAL_BUTTON; i++){
            mouseOver[i] = 0;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < TOTAL_BUTTON; i++){
            bool inside = 0;

            if(buttonBox[i].x < x && x < buttonBox[i].x + BUTTON_WIDTH && buttonBox[i].y < y && y < buttonBox[i].y + BUTTON_HEIGHT){
                inside = 1;
            }
            if(inside){
                switch(e.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if(i == PLAY)
                            state = PLAY_STATE;
                        if(i == QUIT)
                            state = QUIT_STATE;
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
    mWindow.render(mTexture[MENU_TEXTURE], 0, 0, &backgroundClip, 0, NULL, SDL_FLIP_NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i = 0; i < TOTAL_BUTTON; i++){
        mWindow.render(mTexture[MENU_TEXTURE], buttonBox[i].x , buttonBox[i].y ,
                        &buttonClip[i][mouseOver[i]], 0, NULL, SDL_FLIP_NONE, buttonBox[i].w , buttonBox[i].h);
    }
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
