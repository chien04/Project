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


void menu::handle(SDL_Event &e, int &stateMenu, Mix_Chunk *gameSound[]){
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
                        if(i == PLAY){
                            stateMenu = PLAY_STATE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
                        if(i == QUIT){
                            stateMenu = QUIT_STATE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
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
    backgroundClip = {0, 0, 960, 880};
    restart = false;
        buttonBox[0] = {(SCREEN_WIDTH - RESTART_GAME_WIDTH) / 2 + RESTART_GAME_WIDTH / 4 - 100 / 2,
                         (SCREEN_HEIGHT - RESTART_GAME_HEIGHT) / 2 + RESTART_GAME_HEIGHT *3 /4 - 100 /2 - 20, 100, 100};
        buttonBox[1] = {(SCREEN_WIDTH - RESTART_GAME_WIDTH) / 2 + RESTART_GAME_WIDTH * 3/ 4 - 100 / 2,
                         (SCREEN_HEIGHT - RESTART_GAME_HEIGHT) / 2 + RESTART_GAME_HEIGHT * 3 /4 - 100 /2 - 20 , 100, 100};
    int x = 976;
    for(int i = 0; i < TOTAL_BUTTONRELOAD; i++){
        buttonClip[i][0] = {0, x, 208, 208};
        buttonClip[i][1] = {240, x, 208, 208};
        mouseOver[i] = 0;
        x += 240;
    }

}

void reload::handle(SDL_Event &e, int &stateReload, Mix_Chunk *gameSound[]){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ){
        for(int i = 0; i < TOTAL_BUTTONRELOAD; i++){
            mouseOver[i] = 0;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < TOTAL_BUTTONRELOAD; i++){
            bool inside = 0;
            if(buttonBox[i].x < x && x < buttonBox[i].x + BUTTON_WIDTH/2 && buttonBox[i].y < y && y < buttonBox[i].y + BUTTON_HEIGHT)
                inside = 1;
            if(inside){
//                    std::cout << "cjoe";
                switch(e.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if(i == RELOAD){
                            stateReload = RELOAD_STATE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
                        if(i == MENU){
                            stateReload = MENU_STATE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
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

void reload::render(createWindow mWindow, SDL_Texture* mTexture[]){

    mWindow.render(mTexture[MENU_TEXTURE], SCREEN_WIDTH/2 - RESTART_GAME_WIDTH/2, SCREEN_HEIGHT/2 - RESTART_GAME_HEIGHT/2, &backgroundClip,
                   0, NULL, SDL_FLIP_NONE, RESTART_GAME_WIDTH, RESTART_GAME_HEIGHT*11/12);
    for(int i = 0; i < TOTAL_BUTTONRELOAD; i++){
            mWindow.render(mTexture[MENU_TEXTURE], buttonBox[i].x, buttonBox[i].y, &buttonClip[i][mouseOver[i]],
                   0, NULL, SDL_FLIP_NONE, BUTTON_WIDTH/2, BUTTON_HEIGHT);
    }

}

bool reload::getRestart(){
    return restart;
}

pause::pause(){
    backgroundClip = {1968, 1504, 988, 880};
    for(int i = 0; i < TOTAL_BUTTONPAUSE; i++)
    buttonBox[i] = {(SCREEN_WIDTH - RESTART_GAME_WIDTH) / 2 + RESTART_GAME_WIDTH *(i +  1)/ 4 - 100 / 2,
                         (SCREEN_HEIGHT - RESTART_GAME_HEIGHT) / 2 + RESTART_GAME_HEIGHT *3 /4 - 100 /2 - 20, 100, 100};
    int x = 976;
    for(int i= 0; i < TOTAL_BUTTONPAUSE; i++){
        buttonClip[i][0] = {0, x, 208, 208};
        buttonClip[i][1] = {240, x, 208, 208};
        mouseOver[i] = 0;
        x += 240;
    }
}

void pause::handle(SDL_Event &e, int& statePause, Mix_Chunk *gameSound[]){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ){
        for(int i = 0; i < TOTAL_BUTTONPAUSE; i++){
            mouseOver[i] = 0;
        }
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < TOTAL_BUTTONPAUSE; i++){
            bool inside = 0;
            if(buttonBox[i].x < x && x < buttonBox[i].x + BUTTON_WIDTH/2 && buttonBox[i].y < y && y < buttonBox[i].y + BUTTON_HEIGHT)
                inside = 1;
            if(inside){

                switch(e.type){
                    case SDL_MOUSEBUTTONDOWN:
                        if(i == CONTINUTE){
                            statePause = CONTINUTE_STATE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
                        if(i == RESTART){
                            statePause = RELOAD_STATEPAUSE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
                        if(i == MENU){
                            statePause = MENU_STATEPAUSE;
                            Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                        }
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

void pause::render(createWindow mWindow, SDL_Texture* mTexture[]){
    mWindow.render(mTexture[MENU_TEXTURE], SCREEN_WIDTH/2 - RESTART_GAME_WIDTH/2, SCREEN_HEIGHT/2 - RESTART_GAME_HEIGHT/2, &backgroundClip,
                   0, NULL, SDL_FLIP_NONE, RESTART_GAME_WIDTH, RESTART_GAME_HEIGHT*11/12);
    for(int i = 0; i < TOTAL_BUTTONPAUSE; i++){
            mWindow.render(mTexture[MENU_TEXTURE], buttonBox[i].x, buttonBox[i].y, &buttonClip[i][mouseOver[i]],
                   0, NULL, SDL_FLIP_NONE, BUTTON_WIDTH/2, BUTTON_HEIGHT);
    }
}
