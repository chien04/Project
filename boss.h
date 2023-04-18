#ifndef BOSS_H
#define BOSS_H

#include "base.h"
#include "tile_map.h"
class boss{
public:
    boss();

    void createClip();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool touchesWall(SDL_Rect boxBoss, tile tiles[]);
    void move(tile tiles);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]);

private:
    SDL_Rect boxBoss;
    double velX, velY;

    SDL_RendererFlip flip;
    SDL_Rect bossIdle[BOSS_IDLE];
    int frame_idle;
};

#endif // BOSS_H
