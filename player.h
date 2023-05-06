#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "base.h"
#include "tile_map.h"
class player{
public:
    player();

    void createPlayerClip();
//    void createEffectTexture();

    void handle(SDL_Event &e, Mix_Chunk *gameSound[]);
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkCollisionTrap(SDL_Rect a, SDL_Rect b);
    bool touchesWall( SDL_Rect  boxPlayer, tile tiles[] );
    void move(tile tiles[]);

    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], Mix_Chunk *gameSound[]);
    SDL_Rect getBox();
    int getVelX();
    SDL_RendererFlip getFlip();
    bool check();

    int getPosX();
    bool getIsttacking();
    void setIsTakeHit(int damage);
    bool isTakeHitByMonster();
    bool getIsDeath();
    void setHP();
    void setExp();
    bool getAttackMonsterByShot();
    SDL_Rect getBoxShot();
    void setPause();
    bool getPause();
    int getHealingFull();
    int getExpFull();
private:
    int cnt_jump;
    SDL_Rect boxPlayer;
    double velX, velY;
    SDL_RendererFlip flip;
    int frame;
    int frame_attack;
    int frame_takehit;
    int frame_death;
    int frame_skill;
    int frame_player_attack_skill;
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
    SDL_Rect mPlayerExp[PLAYER_EXP];
    SDL_Rect mplayerAttackSkill[PLAYER_ATTACK];
    SDL_Rect mAttackSkill[ATTACK_SKILL];
    SDL_Rect boxChestClip[TOTAL_ITEM];
    std::vector<SDL_Rect> boxChestSliver;
    std::vector<SDL_Rect> boxChestGold;

    SDL_Rect mItem[TOTAL_ITEM];
    SDL_Rect boxShot;
    SDL_Rect boxCam;
    int hp;
    int healing_full;
    int count_healingfull;
    int count_expfull;
    int exp;
    int exp_full;
    bool attackPlayer;
    bool attackSkill;
    bool isShot;
    bool attackMonsterByShot;
    int cnt_trap;
    bool isPause;
    SDL_Rect boxPause;
    SDL_Rect boxPauseClip;

};


#endif // PLAYER_H
