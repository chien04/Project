#include "player.h"
#include "game.h"
#include "hangso_const.h"
#include <time.h>
#include <stdlib.h>
#include "monster.h"
player::player()
{
    cnt_jump = 0;
    boxPlayer.x = 16500;
    boxPlayer.y = 0;
    boxPlayer.w = PLAYER_WIDTH;
    boxPlayer.h = PLAYER_HEIGHT;
    velX = 0;
    velY = PLAYER_VEL;
    flip = SDL_FLIP_NONE;
    frame = 0;
    frame_attack = 0;
    frame_takehit = 0;
    frame_death = 0;
    frame_skill = 0;
    frame_player_attack_skill = 0;
    on_ground = false;
    isIdle = false;
    isRunning = false;
    isJump = false;
    attacking = false;
    attackMonster = false;
    isTakeHit = false;
    isDeath = false;
    createPlayerClip();
//    createEffectTexture();
    hp = 5;
    exp = 0;
    attackPlayer = false;
    attackSkill = false;
    isShot = false;
    cnt_trap = 0;
    SDL_Rect boxShot = {0, 0, 640, 64};
    SDL_Rect boxCam = {0, 0, 640, 64};

}

void player::createPlayerClip()
{
    int sum = 0;
    for(int i = 0; i < PLAYER_IDLE; i++)
    {
        mPlayerIdle[i] = {sum, 16, 32, 48};
        sum += 48;
    }
    sum = 16;
    for(int i = 0; i < PLAYER_RUN; i++)
    {
        mPlayerRun[i] = {sum, 384, 32, 48};
        sum += 48;
    }
    sum = 0;
    for(int i = 0; i < PLAYER_JUMP; i++)
    {
        mPlayerJump[i] = {sum, 288, 64, 64};
        sum += 64;
    }
    sum = 0;
    for(int i = 0; i < PLAYER_ATTACK; i++)
    {
        mPlayerAttack[i] = {sum, 160, 96, 80};
        sum += 96;
    }
    mPlayerTakeHit[0] = {560, 512, 288, 160};
    mPlayerTakeHit[1] = {0, 512, 288, 160};
    mPlayerTakeHit[2] = {288, 512, 288, 160};

    sum = 0;

    for(int i = 0; i < PLAYER_DEATH; i++)
    {
        mPlayerDeath[i] = {sum, 96, 64, 64};
        sum += 64;
    }
    sum = 0;
    for(int i = PLAYER_HEALTH - 1; i >= 0; i--)
    {
        mPlayeHeath[i] = {0, sum, 672, 224};
        sum += 224;
    }
    sum = 0;
    for(int i = 0; i < ATTACK_SKILL; i++){
        mAttackSkill[i] = {0, sum, 400, 128};
        sum += 128;
    }
    sum = 0;
    for(int i = 0; i < PLAYER_ATTACK; i++){
        mplayerAttackSkill[i] = {sum, 656, 96, 80};
        sum += 96;
    }
    sum = 1408;
    for(int i = 0; i < PLAYER_EXP; i++){
        mPlayerExp[i] = {0, sum, 384, 64};
        sum += 80;
    }
}

void player::handle(SDL_Event& e)
{
    if(isDeath)
        return;
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            velX += PLAYER_VEL;
            break;
        case SDLK_LEFT:
            velX -= PLAYER_VEL;
            break;
        case SDLK_UP:
            if(on_ground && velY > 0)
            {
                velY = -PLAYER_VEL;
                on_ground = false;
                cnt_jump = 0;
            }
            break;
        case SDLK_a:
            if(attacking == false && attackSkill == false)
            {
                attacking = true;
            }
            break;
        case SDLK_w:
            if(!attackSkill && !attackSkill)
                attackSkill = true;
            break;
        }
    }
    else if(e.type == SDL_KEYUP)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            velX -= PLAYER_VEL;
            break;
        case SDLK_LEFT:
            velX += PLAYER_VEL;
            break;
        }
    }
}

bool player::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y - 24;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}


bool player::checkCollisionTrap(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y + b.h/2;
    bottomB = b.y + b.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool player::touchesWall( SDL_Rect boxPlayer, tile tiles[] )
{
    //Go through the tiles
    std::set<int> mySet;
    for(int i = 0; i < 30; i++){
        mySet.insert(i);
    }
    mySet.insert(-1);
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if(tiles[i].getTileType() == 12 || tiles[i].getTileType() == 13){
            if(checkCollisionTrap(boxPlayer, tiles[i].getBox()))
                attackPlayer = true;
        }
        //If the tile is a wall type tile
        if(!mySet.count(tiles[ i ].getTileType()))
        {
            //If the collision boxPlayer touches the wall tile
            if( checkCollision( boxPlayer, tiles[ i ].getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void player::move(tile tiles[])
{
    if(isDeath)
        return;
    if(velY < 0)
    {
        cnt_jump++;
        if(cnt_jump >= PLAYER_MAX_JUMP)
        {
            cnt_jump = 0;
            velY *= -1;
        }
    }

    boxPlayer.x += velX;
    if(boxPlayer.x < 0 || boxPlayer.x + PLAYER_WIDTH > WIDTH_MAP || touchesWall(boxPlayer, tiles) )
    {
        boxPlayer.x -= velX;
    }
    boxPlayer.y += velY;
    if(boxPlayer.y < 0 || boxPlayer.y + PLAYER_HEIGHT > HEIGHT_MAP || touchesWall(boxPlayer, tiles))
    {
        boxPlayer.y -= velY;
        on_ground = true;
    }
    else
        on_ground = false;

    if(on_ground == true && velY < 0)
        on_ground = false;

    if(on_ground == false && velY >= 0){
        if(velY == PLAYER_VEL)
        velY = 0;
        velY += 0.08;
    }
    if(on_ground && velY > 0)
        velY = PLAYER_VEL;
    if(velX == 0 && on_ground == true && attacking == false && attackSkill == false)
    {
        isIdle = true;
        isRunning = false;
        isJump = false;
    }
    if(velX != 0 && on_ground == true && attacking == false && attackSkill == false)
    {
        isIdle = false;
        isRunning = true;
        isJump = false;
    }
    if(on_ground == false && attacking == false && attackSkill == false)
    {
        isJump = true;
        isIdle = false;
        isRunning = false;
    }
    if(attacking)
    {
        isIdle = false;
        isRunning = false;
        isJump = false;
        attackSkill = false;
    }
    if(attackSkill)
    {
        isIdle = false;
        isRunning = false;
        isJump = false;
        attacking = false;
    }
    if(isShot)
        return;
    if(velX < 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if(velX > 0)
    {
        flip = SDL_FLIP_NONE;
    }


}
void player::setIsTakeHit(int damage)
{
    if(!isTakeHit){
        if(attackPlayer && cnt_trap == 120) {
            hp -= 1;
            isTakeHit = true;
            attackPlayer = false;
            cnt_trap = 0;
        }
        if(damage != 0){
            isTakeHit = true;
            hp -= damage;
        }
    }

}

bool player::isTakeHitByMonster()
{
    return isTakeHit;
}

void player::setHP(){
    if(hp < PLAYER_HEALTH - 1)
        hp += 1;
}
void player::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[])
{
    cnt_trap++;
    if(cnt_trap >= 120)
        cnt_trap = 120;

    SDL_Rect bp = {boxPlayer.x - camera.x , boxPlayer.y - camera.y, PLAYER_WIDTH, PLAYER_HEIGHT};
    mWindow.renderBox(bp);
    for(int i = 0; i < PLAYER_HEALTH; i++)
    {
        if(i == hp)
            mWindow.render(mTexture[HEALTH_TEXTURE], 10, 30,
                           &mPlayeHeath[i], 0, NULL, SDL_FLIP_NONE, 210, 70);
    }
    for(int i= 0; i < PLAYER_EXP; i++){
        if(i == exp){
            mWindow.render(mTexture[HEALTH_TEXTURE], 50, 100, &mPlayerExp[i], 0, NULL, SDL_FLIP_NONE, 180, 30);
        }
    }
    if(isDeath)
        return;
    if(hp > 0 )
    {
        if(!isTakeHit)
        {
            if(isIdle)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                               &mPlayerIdle[frame/(PLAYER_IDLE*4)], 0, NULL, flip, PLAYER_WIDTH, PLAYER_HEIGHT);
                frame++;
                if(frame / (PLAYER_IDLE*4) >= PLAYER_IDLE)
                    frame = 0;
            }
            if(isRunning)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                               &mPlayerRun[frame/PLAYER_RUN], 0, NULL, flip, PLAYER_WIDTH, PLAYER_HEIGHT);
                frame++;
                if(frame / PLAYER_RUN >= PLAYER_RUN)
                {
                    frame = 0;
                }
            }
            if(isJump)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 24, boxPlayer.y - camera.y - 30,
                               &mPlayerJump[frame/PLAYER_JUMP], 0, NULL, flip, PLAYER_WIDTH * 2, PLAYER_HEIGHT*4/3);
                frame++;
                if(frame / PLAYER_JUMP >= PLAYER_JUMP)
                {
                    frame = 0;
                }
            }
            if(attacking)
            {
                if(flip == SDL_FLIP_HORIZONTAL)
                {
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 48, boxPlayer.y - camera.y - 40,
                                   &mPlayerAttack[frame_attack/PLAYER_ATTACK], 0, NULL, flip, PLAYER_WIDTH*3, PLAYER_HEIGHT*5/3);
                }
                else if(flip == SDL_FLIP_NONE)
                {
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 64, boxPlayer.y - camera.y - 40,
                                   &mPlayerAttack[frame_attack/PLAYER_ATTACK], 0, NULL, flip, PLAYER_WIDTH*3, PLAYER_HEIGHT*5/3);
                }
                if(frame_attack == 16)
                {
                    attackMonster = true;
                }
                else
                    attackMonster = false;

                frame_attack++;
                if(frame_attack / PLAYER_ATTACK >= PLAYER_ATTACK)
                {
                    frame_attack = 0;
                    attacking = false;
                }
            }
            if(attackSkill){
                if(flip == SDL_FLIP_HORIZONTAL)
                {
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 48, boxPlayer.y - camera.y - 40,
                                   &mplayerAttackSkill[frame_player_attack_skill/(PLAYER_ATTACK*2)], 0, NULL, flip, PLAYER_WIDTH*3, PLAYER_HEIGHT*5/3);
                }
                else if(flip == SDL_FLIP_NONE)
                {
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 64, boxPlayer.y - camera.y - 40,
                                   &mplayerAttackSkill[frame_player_attack_skill/(PLAYER_ATTACK*2)], 0, NULL, flip, PLAYER_WIDTH*3, PLAYER_HEIGHT*5/3);
                }
                frame_player_attack_skill++;
                if(frame_player_attack_skill / (PLAYER_ATTACK*2) >= PLAYER_ATTACK){
                    frame_player_attack_skill = 0;
                    attackSkill = false;
                }
                if(frame_player_attack_skill == 80){
                    isShot = true;
                }
            }
            if(isShot){
                if(flip == SDL_FLIP_NONE){
                    mWindow.render(mTexture[SKILL_TEXTURE], boxPlayer.x - camera.x - 96, boxPlayer.y - camera.y,
                                &mAttackSkill[frame_skill/ATTACK_SKILL], 0, NULL, flip, 1000, 64);
                    boxShot.x = boxPlayer.x - 48 + boxPlayer.w*2 + 7;
                    boxShot.y = boxPlayer.y;
                    boxShot.w = 800;
                    boxShot.h = 50;
                    boxCam.x = boxPlayer.x - camera.x - 48 + boxPlayer.w *2 + 7;
                    boxCam.y = boxPlayer.y - camera.y;
                    boxCam.w = 800;
                    boxCam.h = 50;
                }
                if(flip == SDL_FLIP_HORIZONTAL){
                    mWindow.render(mTexture[SKILL_TEXTURE], boxPlayer.x - camera.x - 856, boxPlayer.y - camera.y,
                                &mAttackSkill[frame_skill/ATTACK_SKILL], 0, NULL, flip, 1000, 64);
                    boxShot.x = boxPlayer.x - 808 + 7;
                    boxShot.y = boxPlayer.y;
                    boxShot.w = 800;
                    boxShot.h = 50;
                    boxCam.x = boxPlayer.x - 808 - camera.x+ 7;
                    boxCam.y = boxPlayer.y - camera.y;
                    boxCam.w = 800;
                    boxCam.h = 50;
                }

                if(frame_skill == 54)
                    attackMonsterByShot = true;
                else
                    attackMonsterByShot = false;
                frame_skill++;
                if(frame_skill / ATTACK_SKILL >= ATTACK_SKILL){
                    frame_skill = 0;
                    isShot = false;
                }
            }
        }
        else
        {
            attackSkill = false;
            frame_attack = 0;
            frame_player_attack_skill = 0;
            frame_skill = 0;
            isShot = false;
            if(flip == SDL_FLIP_NONE)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 160, boxPlayer.y - camera.y - 100,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*3)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
                frame_takehit++;
                if(frame_takehit / (PLAYER_TAKEHIT*3) >= PLAYER_TAKEHIT)
                {
                    frame_takehit = 0;
                    isTakeHit = false;
                }
            }
            else if(flip == SDL_FLIP_HORIZONTAL)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 246, boxPlayer.y - camera.y - 100,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*5)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
                frame_takehit++;
                if(frame_takehit / (PLAYER_TAKEHIT*5) >= PLAYER_TAKEHIT)
                {
                    frame_takehit = 0;
                    isTakeHit = false;
                }
            }
        }
    }
    if(hp <= 0)
    {
        mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                       &mPlayerDeath[frame_death/(PLAYER_DEATH*2)], 0, NULL, flip, PLAYER_WIDTH*2, PLAYER_HEIGHT*4/3);
        frame_death++;
        if(frame_death / (PLAYER_DEATH*2) >= PLAYER_DEATH)
        {
            frame_death = 0;
            isDeath = true;
        }
    }
    mWindow.renderBox(boxCam);


}

int player::getVelX()
{
    return velX;
}

SDL_RendererFlip player::getFlip()
{
    return flip;
}

int player::getPosX()
{
    return boxPlayer.x;
}

bool player::getIsttacking()
{
    return attackMonster;
}

SDL_Rect player::getBox()
{
    return boxPlayer;
}

bool player::getAttackMonsterByShot(){
    return attackMonsterByShot;
}

SDL_Rect player::getBoxShot(){
    return boxShot;
}
bool player::getIsDeath(){
    return isDeath;
}
