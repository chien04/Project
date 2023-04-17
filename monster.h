#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include "base.h"
#include "tile_map.h"
#include "player.h"
#include "hangso_const.h"

class monster{
public:
    monster(int x = 0, int y = 0);
    void createMonsterClip();

    bool checkCollision(SDL_Rect a, SDL_Rect b);

    bool touchesWall(SDL_Rect boxMonster, tile tiles[]);
    void move(player mPlayer, tile tiles[], int pos_x);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mPlayer);

    int getPosX();
    bool getMonsterAttack();

private:
    SDL_Rect boxMonster;
    double velX, velY;

    SDL_RendererFlip flip;

    SDL_Rect monsterIdle[MONSTER_IDLE];
    SDL_Rect monsterRun[MONSTER_RUN];
    SDL_Rect monsterAttack[MONSTER_ATTACK];
    SDL_Rect monsterDeath[MONSTER_DEATH];
    SDL_Rect monsterKnockBack[MONSTER_KNOCKBACK];
    SDL_Rect monsterHP[MONSTER_HP];
    int frame[TOTAL_FRAME];
    bool on_ground;
    bool isIdle;
    bool isRunning;
    bool inZone;
    bool isAttacking;
    bool attackPlayer;
    bool attackPlayerFlip;
    bool isHitting;
    int hp;
    bool is_death;
    int cnt;

};

#endif // MONSTER_H
