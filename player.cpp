#include "player.h"
#include "game.h"
#include "hangso_const.h"
#include <time.h>
#include <stdlib.h>
#include "monster.h"
player::player()
{
    cnt_jump = 0;
    boxPlayer.x = 60;
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
    healing_full = 0;
    count_healingfull = 0;
    exp_full = 0;
    exp = 6;
    count_expfull = 0;
    attackPlayer = false;
    attackSkill = false;
    isShot = false;
    cnt_trap = 0;
    SDL_Rect boxShot = {0, 0, 640, 64};
    SDL_Rect boxCam = {0, 0, 640, 64};

    isPause = false;
    boxPause = {SCREEN_WIDTH - 120, 20 , 100, 100};
    boxPauseClip = {496, 976, 208, 208};
    SDL_Rect rect0{5088, 1548, 48, 48};
    SDL_Rect rect1{8160, 1680, 48, 48};
    SDL_Rect rect2{12672, 1776, 48, 48};
    boxChestSliver.push_back(rect0);
    boxChestSliver.push_back(rect1);
    boxChestSliver.push_back(rect2);
    SDL_Rect gold{5568, 1008, 48, 48};
    SDL_Rect gold1{11230, 1056, 48, 48};
    boxChestGold.push_back(gold);
    boxChestGold.push_back(gold1);
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
        mplayerAttackSkill[i] = {sum, 704, 96, 80};
        sum += 96;
    }
    sum = 1408;
    for(int i = PLAYER_EXP - 1; i >= 0; i--){
        mPlayerExp[i] = {0, sum, 384, 64};
        sum += 80;
    }
    sum = 464;
    for(int i = 0; i < TOTAL_ITEM; i++){
        mItem[i] = {0, sum, 192, 128};
        sum += 144;
    }
    sum = 0;
    for(int i = 0; i < TOTAL_ITEM; i++){
        boxChestClip[i] = {272, sum, 48, 48};
        sum += 48;
    }
}

void player::handle(SDL_Event& e, Mix_Chunk *gameSound[])
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
                Mix_PlayChannel(-1, gameSound[PLAYER_JUMPSOUND], 0);
            }
            break;
        case SDLK_e:
            if(healing_full > 0){
                hp = 5;
                healing_full--;
            }
            break;
        case SDLK_r:
            if(exp_full > 0){
                exp = 6;
                exp_full--;
            }
            break;
        case SDLK_a:
            if(attacking == false && attackSkill == false)
            {
                attacking = true;
                Mix_PlayChannel(-1, gameSound[PLAYER_ATTACKSOUND], 0);
            }
            break;
        case SDLK_w:
            if(!attackSkill && !attackSkill && exp == 6)
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
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION){
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = false;
        if(boxPause.x < x && x < boxPause.x + boxPause.w && boxPause.y < y && y < boxPause.y + boxPause.h){
            inside = true;
        }
        if(inside){
            switch(e.type){
                case SDL_MOUSEBUTTONDOWN:
                    isPause = true;
                    Mix_PlayChannel(-1, gameSound[PRESS_BUTTON], 0);
                    break;
                default:
                    break;
            }
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
    if(isPause)
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

    for(int i = 0; i < boxChestGold.size(); i++){
        if(checkCollision(boxPlayer, boxChestGold[i])){
            if(getIsttacking()){
                healing_full++;
                boxChestGold.erase(boxChestGold.begin() + i);
            }
        }
    }
    for(int i = 0; i < boxChestSliver.size(); i++){
        if(checkCollision(boxPlayer, boxChestSliver[i])){
            if(getIsttacking()){
                exp_full++;
                boxChestSliver.erase(boxChestSliver.begin() + i);
            }
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

void player::setExp(){
    if(exp < PLAYER_EXP - 1)
        exp += 1;
}
void player::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], Mix_Chunk *gameSound[])
{
    cnt_trap++;
    if(cnt_trap >= 120)
        cnt_trap = 120;

    SDL_Rect bp = {boxPlayer.x - camera.x , boxPlayer.y - camera.y, PLAYER_WIDTH, PLAYER_HEIGHT};

    //render chest
    for(int i = 0; i < boxChestGold.size(); i++){
        mWindow.render(mTexture[PLAYER_TEXTURE], boxChestGold[i].x - camera.x, boxChestGold[i].y - camera.y,
            &boxChestClip[1], 0, NULL, SDL_FLIP_NONE, 48, 48);
    }
    for(int i = 0; i < boxChestSliver.size(); i++){
        mWindow.render(mTexture[PLAYER_TEXTURE], boxChestSliver[i].x - camera.x, boxChestSliver[i].y - camera.y,
            &boxChestClip[0], 0, NULL, SDL_FLIP_NONE, 48, 48);
    }
    //render player item
    mWindow.render(mTexture[HP_ENEMY_TEXTURE], 30, 150,
        &mItem[0], 0, NULL, SDL_FLIP_NONE, 45, 30);
    mWindow.render(mTexture[HP_ENEMY_TEXTURE], 150, 150,
        &mItem[1], 0, NULL, SDL_FLIP_NONE, 45, 30);
    for(int i = 0; i < PLAYER_HEALTH; i++)
    {
        if(i == hp)
            mWindow.render(mTexture[HEALTH_TEXTURE], 10, 30,
                           &mPlayeHeath[i], 0, NULL, SDL_FLIP_NONE, 210, 70);
    }
    for(int i= 0; i < PLAYER_EXP; i++){
        if(i == exp){
            mWindow.render(mTexture[HEALTH_TEXTURE], 65, 90, &mPlayerExp[i], 0, NULL, SDL_FLIP_NONE, 150, 25);
        }
    }
    mWindow.render(mTexture[MENU_TEXTURE], boxPause.x, boxPause.y, &boxPauseClip, 0, NULL, SDL_FLIP_NONE, 100, 100);
    if(isDeath)
        return;
    if(hp > 0)
    {
        if(!isTakeHit)
        {
            if(isIdle)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                               &mPlayerIdle[frame/(PLAYER_IDLE*4)], 0, NULL, flip, PLAYER_WIDTH, PLAYER_HEIGHT);
                if(!isPause)
                    frame++;
                if(frame / (PLAYER_IDLE*4) >= PLAYER_IDLE)
                    frame = 0;
            }
            if(isRunning)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                               &mPlayerRun[frame/PLAYER_RUN], 0, NULL, flip, PLAYER_WIDTH, PLAYER_HEIGHT);
                if(frame == 0)
                    Mix_PlayChannel(-1, gameSound[PLAYER_RUNSOUND], 0);
                if(!isPause)
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
                if(!isPause)
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
                if(!isPause)
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
                if(frame_player_attack_skill == 80)
                    Mix_PlayChannel(-1, gameSound[PLAYER_ATTACKSKILLSOUND], 0);
                if(!isPause)
                frame_player_attack_skill++;
                if(frame_player_attack_skill / (PLAYER_ATTACK*2) >= PLAYER_ATTACK){
                    frame_player_attack_skill = 0;
                    attackSkill = false;
                    exp = 0;
                }
                if(frame_player_attack_skill == 80){
                    isShot = true;
                }
            }
            if(isShot){
                if(flip == SDL_FLIP_NONE){
                    mWindow.render(mTexture[SKILL_TEXTURE], boxPlayer.x - camera.x - 96, boxPlayer.y - camera.y - 16,
                                &mAttackSkill[frame_skill/ATTACK_SKILL], 0, NULL, flip, 1000, 80);
                    boxShot.x = boxPlayer.x - 48 + boxPlayer.w*2 + 20;
                    boxShot.y = boxPlayer.y;
                    boxShot.w = 800;
                    boxShot.h = 50;
                }
                if(flip == SDL_FLIP_HORIZONTAL){
                    mWindow.render(mTexture[SKILL_TEXTURE], boxPlayer.x - camera.x - 856, boxPlayer.y - camera.y - 16,
                                &mAttackSkill[frame_skill/ATTACK_SKILL], 0, NULL, flip, 1000, 80);
                    boxShot.x = boxPlayer.x - 808 + 20;
                    boxShot.y = boxPlayer.y;
                    boxShot.w = 800;
                    boxShot.h = 50;
                }

                if(frame_skill == 54)
                    attackMonsterByShot = true;
                else
                    attackMonsterByShot = false;
                if(!isPause)
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
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 160, boxPlayer.y - camera.y - 100,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*5)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
            if(flip == SDL_FLIP_HORIZONTAL)
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 246, boxPlayer.y - camera.y - 100,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*5)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
                if(frame_takehit == 0)
                    Mix_PlayChannel(-1, gameSound[PLAYER_DAMAGESOUND], 0);
                if(!isPause)
                    frame_takehit++;
                if(frame_takehit / (PLAYER_TAKEHIT*5) >= PLAYER_TAKEHIT)
                {
                    frame_takehit = 0;
                    isTakeHit = false;
                }
        }
    }
    if(hp <= 0)
    {
        mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x, boxPlayer.y - camera.y,
                       &mPlayerDeath[frame_death/(PLAYER_DEATH*2)], 0, NULL, flip, PLAYER_WIDTH*2, PLAYER_HEIGHT*4/3);
        if(frame_death == 0)
            Mix_PlayChannel(-1, gameSound[PLAYER_DEATHSOUND], 0);
        if(!isPause)
            frame_death++;
        if(frame_death / (PLAYER_DEATH*2) >= PLAYER_DEATH)
        {
            frame_death = 0;
            isDeath = true;
        }
    }
//    mWindow.renderBox(boxCam);


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

void player::setPause(){
    isPause = false;
}
bool player::getPause(){
    return isPause;
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

int player::getHealingFull(){
    return healing_full;
}

int player::getExpFull(){
    return exp_full;
}
