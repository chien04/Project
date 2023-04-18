#include "boss.h"

boss::boss(){
    boxBoss = {0, 0, BOSS_WIDTH, BOSS_HEIGHT};
    velX = 0;
    velY = 2;
    flip = SDL_FLIP_NONE;
    frame_idle = 0;
}

void boss::createClip(){
    int sum = 0;
    for(int i = 0; i < BOSS_IDLE; i++){
        bossIdle[i] = {sum , 0, 48, 64};
        sum += 160;
    }
}


void boss::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]){
    mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                   &bossIdle[frame_idle / BOSS_IDLE], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
}
