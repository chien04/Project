#ifndef PLAYER_H
#define PLAYER_H

#include "base.h"
#include "tile_map.h"
class player{
public:
    player();

    void createPlayerClip();
    void createEffectTexture();

    void handle(SDL_Event &e);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

    bool touchesWall( SDL_Rect  boxPlayer, tile tiles[] );
    void move(tile tiles[]);

    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]);
    SDL_Rect getBox();
    int getVelX();
    SDL_RendererFlip getFlip();
    bool check();

    int getPosX();
    bool getIsttacking();
    void setIsTakeHit(bool x, bool y);
    bool isTakeHitByMonster();
    bool getIsDeath();

private:
    int cnt_jump;
    SDL_Rect boxPlayer;
    int velX, velY;
    SDL_RendererFlip flip;
    int frame;
    int frame_attack;
    int frame_takehit;
    int frame_death;
    bool on_ground;
    bool isIdle;
    bool isRunning;
    bool isJump;
    bool attacking;
    bool attackMonster;
    bool isTakeHit;
    bool isDeath;
    SDL_Rect mPlayerIdle[PLAYER_IDLE];
    SDL_Rect mPlayerRun[PLAYER_RUN];
    SDL_Rect mPlayerJump[PLAYER_JUMP];
    SDL_Rect mPlayerAttack[PLAYER_ATTACK];
    SDL_Rect mPlayerTakeHit[PLAYER_TAKEHIT];
    SDL_Rect mPlayerDeath[PLAYER_DEATH];
    SDL_Rect mPlayeHeath[PLAYER_HEALTH];
    SDL_Rect mEffectClip[EFFECT_CLIP];

    int hp;
};


#endif // PLAYER_H
