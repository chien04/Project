#ifndef BOSS_H
#define BOSS_H

#include <vector>
#include "base.h"
#include "tile_map.h"
#include "player.h"
#include "ice_ball.h"
#include "monster.h"
#include "wizard.h"
class boss{
public:
    boss();

    void createClip();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool touchesWall(SDL_Rect boxBoss, tile tiles[]);
    void move(tile tiles[], player boxPlayer);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mPlayer, Mix_Chunk *gameSound[]);
    void setPosX();
    bool getAttackPlayer();
    void setTotal_damage();
    int getTotal_damage();
    bool getIsTakeHit();
    void setCnt();
    bool getCnt();
    int getPosX();
    bool getDeath();
private:
    SDL_Rect boxBoss;
    int velX, velY;
    int posX;
    SDL_RendererFlip flip;
    SDL_RendererFlip flip_ball;
    SDL_Rect bossIdle[BOSS_IDLE];
    SDL_Rect bossRun[BOSS_RUNNING];
    SDL_Rect bossTakeHit[BOSS_TAKEHIT];
    SDL_Rect bossAttack1[BOSS_ATTACK1];
    SDL_Rect bossAttack2[BOSS_ATTACK2];
    SDL_Rect bossSkill2[BOSS_SKILL2];
    SDL_Rect bossHP[BOSS_HP];
    SDL_Rect bossDeath[BOSS_DEATH];
    int frame_idle;
    int frame_run;
    int random_posX;
    int frame_takehit;
    int frame_attack1;
    int frame_attack2;
    int frame_skill;
    int frame_death;
    std::vector<fire_ball> mBall;
    bool ban;
    bool lightning;
    bool isIdle;
    bool isRunning;
    bool isAttacking;
    bool attackPlayer;
    bool isTakeHit;
    bool take_hit;
    bool isDeath;
    int hp;
    int res;
    int lightningPosX;
    SDL_Rect lightningBox;
    std::vector<monster> mMonster;
    std::vector<wizard> mWizard;
    int cnt;
    int total_damage;

};
#endif // BOSS_H
