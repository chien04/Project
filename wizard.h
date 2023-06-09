#ifndef WIZARD_H
#define WIZARD_H
#include <vector>
#include "base.h"
#include "ice_ball.h"
#include "tile_map.h"
#include "player.h"
class wizard{
public:
    wizard(int x = 0, int y = 0);

    void createWizardClip();

    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkCollisionTrap(SDL_Rect a, SDL_Rect b);
    bool touchesWall(SDL_Rect boxArcher, tile tiles[]);

    void move(player mPlayer, tile tiles[]);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mplayer, Mix_Chunk *gameSound[]);
    void setPosX();
    int getPosX();
    int getPosY();
    SDL_Rect getBoxWizard();
    bool getShot();
    SDL_RendererFlip getFlip();
    bool getAttackPlayer();
    bool getIsTakeHit();
    bool getDeath();
private:
    SDL_Rect boxWizard;

    int velX, velY;
    int pos_x;
    SDL_RendererFlip flip;
    SDL_RendererFlip flip_ball;
    std::vector <ice_ball> mBall;
    SDL_Rect wizardIdle[WIZARD_IDLE];
    SDL_Rect wizardAttack[WIZARD_ATTACK];
    SDL_Rect wizardTakeHit[WIZARD_TAKE_HIT];
    SDL_Rect wizardDeath[WIZARD_DEATH];
    SDL_Rect wizardHP[WIZARD_HP];
    int frame[WIZARD_FRAME];
    bool inZone;
    bool isAttacking;
    bool isHitting;
    bool take_hit;
    bool attackPlayer;
    bool isDeath;
    bool shot;
    int cnt;
    int hp;
};




#endif // WIZARD_H
