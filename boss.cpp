#include "boss.h"

boss::boss()
{
    boxBoss = {6240, 0, BOSS_WIDTH, BOSS_HEIGHT};
    velX = BOSS_VEL;
    velY = 10;
    flip = SDL_FLIP_NONE;
    flip_ball = SDL_FLIP_NONE;
    frame_idle = 0;
    frame_run = 0;
    frame_takehit = 0;
    frame_attack1 = 0;
    frame_attack2 = 0;
    frame_skill = 0;
    random_posX = boxBoss.x;
    random_posXcurrent = random_posX;
    ban = false;
    lightning = false;
    isIdle = false;
    isRunning = false;
    isAttacking = false;
    attackPlayer = false;
    isTakeHit = false;
    isDeath = false;
    hp = 6;
    res = 0;
    lightningPosX = 0;
    lightningBox = {0, 0, 128, 256};
    createClip();
}

bool boss::checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
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
bool boss::touchesWall( SDL_Rect boxBoss, tile tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if(tiles[ i ].getTileType() != -1)
        {
            //If the collision box touches the wall tile
            if( checkCollision( boxBoss, tiles[ i ].getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void boss::createClip()
{
    int sum = 32;
    for(int i = 0; i < BOSS_IDLE; i++)
    {
        bossIdle[i] = {sum, 48, 276, 336};
        sum += 960;
    }
    sum = 48;
    for(int i = 0; i < BOSS_ATTACK1; i++)
    {
        bossAttack1[i] = {sum, 3440, 320, 336};
        sum += 480;
    }
    sum = 80;
    for(int i = 0; i < BOSS_ATTACK2; i++)
    {
        bossAttack2[i] = {sum, 1680, 352, 529};
        sum += 480;
    }

    sum = 96;
    for(int i = 0; i < BOSS_RUNNING; i++){
        bossRun[i] = {sum, 1168, 256, 304};
        sum += 480;
    }

    sum = 112;
    for(int i = 0; i < BOSS_SKILL2; i++)
    {
        bossSkill2[i] = {sum, 400, 64, 96};
        sum += 64;
    }
}

void boss::setPosX()
{
    posX = boxBoss.x;
}
void boss::move(tile tiles[], player mPlayer)
{
    boxBoss.y += velY;
    if(boxBoss.y < 0 || boxBoss.y + BOSS_HEIGHT > HEIGHT_MAP || touchesWall(boxBoss, tiles))
    {
        boxBoss.y -= velY;
    }
    if(checkCollision(boxBoss, mPlayer.getBox()))
    {
        if(mPlayer.getIsttacking())
        {
            isTakeHit = true;
            isAttacking = false;
            isIdle = false;
            hp--;
            if(hp < 0)
                hp = 0;
        }
    }

    if(boxBoss.x > mPlayer.getPosX())
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;

    if(ban) {
        if(!isAttacking){
            isIdle = true;
            return;
        }
    }
    if(isAttacking)
        return;


    SDL_Rect boxAttack = {posX - 500, boxBoss.y, posX + 500, BOSS_HEIGHT};
//    if(checkCollision(boxAttack, mPlayer.getBox()))
//    {
////        std::cout << "ch" << std::endl;
//        isAttacking = true;
//        isIdle = false;
//    }

    if(checkCollision(boxAttack, mPlayer.getBox())){
        if(!isAttacking){
            isRunning = true;
            isIdle = false;
        }
    }
    if(isRunning){

        if(boxBoss.x < random_posX){
            flip = SDL_FLIP_NONE;
            boxBoss.x += 1;
        }
        if(boxBoss.x > random_posX){
            flip = SDL_FLIP_HORIZONTAL;
            boxBoss.x -= 1;
        }
        if(boxBoss.x == random_posX){
            setPosX();
            std::cout << boxBoss.x << std::endl;
            random_posXcurrent = random_posX;
            random_posX = rand() % (6760 - 5720 + 1) + 5720;
            isRunning = false;
            isAttacking = true;

        }
    }
    if(!isRunning){
        if(!checkCollision(boxAttack, mPlayer.getBox()))
        {
            isIdle = true;
            isAttacking = false;
        }
    }


}

void boss::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mplayer)
{
    if(!ban)
    {
        flip_ball = flip;
    }
    if(hp > 0)
    {
        if(isRunning)
        {
            mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                           &bossRun[frame_run / BOSS_RUNNING], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
            frame_run++;
            if(frame_run / BOSS_RUNNING >= BOSS_RUNNING){
                frame_run = 0;
            }
        }
        if(isIdle)
        {
            mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                           &bossIdle[frame_idle / BOSS_IDLE], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
            frame_idle++;
            if(frame_idle / BOSS_IDLE >= BOSS_IDLE)
            {
                frame_idle = 0;
            }
        }
        if(isTakeHit)
        {
            mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                           &bossTakeHit[frame_takehit / BOSS_TAKEHIT], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
            frame_takehit = 0;
            if(frame_takehit / BOSS_TAKEHIT >= BOSS_TAKEHIT)
            {
                frame_takehit = 0;
                isTakeHit = false;
            }
        }
        if(isAttacking)
        {
            if(res == 0){
                mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y + 12,
                           &bossAttack1[frame_attack1 / BOSS_ATTACK1], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
                if(frame_attack1 == 0){
                    if(mBall.size() == 0)
                    {
//                    if(frame_attack1 == 0){
                        mBall.push_back(fire_ball(boxBoss, flip_ball));
//                        std::cout << " " << mBall[0].getBan() << std::endl;
                    }
                }

                frame_attack1++;
                if(frame_attack1 == 11 * BOSS_ATTACK1)
                {
                    ban = true;
                }
                if(frame_attack1 / (BOSS_ATTACK1) >= BOSS_ATTACK1)
                {
                    res = rand() % 1;
                    isAttacking = false;
                    frame_attack1 = 0;
                }
            }
            if(res == 1){
                mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                               &bossAttack2[frame_attack2 / BOSS_ATTACK2], 0, NULL, flip, BOSS_WIDTH, BOSS_HEIGHT);
                frame_attack2++;
                if(frame_attack2 / BOSS_ATTACK2 == 9)
                    lightning = true;
                if(frame_attack2 / BOSS_ATTACK2 >= BOSS_ATTACK2)
                {
                    res = rand() % 1;
                    frame_attack2 = 0;
                    isAttacking = false;
                }
            }


       }
            if(ban){
                for(int i = 0; i < mBall.size(); i++)
                {
                    mBall[i].move(flip_ball, mplayer.getBox());
                    if(mBall[i].getBan())
                    {
                        mBall[i].render(mWindow, camera, mTexture);
                    }
                    else
                    {
                        mBall.erase(mBall.begin() + i);
                        ban = false;
                    }
                    if(mBall[i].getAttackPlayer())
                        attackPlayer = true;
                    else
                        attackPlayer = false;
                }
            }
            else
                attackPlayer = false;

//            std::cout << ban << std::endl;
            if(lightning)
            {
                if(frame_skill == 0){
                    lightningPosX = mplayer.getPosX();
                    lightningBox.x = mplayer.getPosX() - 12;
                    lightningBox.y = boxBoss.y - 32;
                    lightningBox.w = 128;
                    lightningBox.h = 256;
                }
                mWindow.render(mTexture[WIZARD_TEXTURE], lightningPosX - 12 - camera.x, boxBoss.y - camera.y - 32,
                               &bossSkill2[frame_skill / (BOSS_SKILL2 * 2)], 0, NULL, SDL_FLIP_NONE, 128, 256);
                frame_skill++;
                if(frame_skill == 88){
                    if(checkCollision(lightningBox, mplayer.getBox())){
                        attackPlayer = true;
                    }
                }
                else
                    attackPlayer = false;
                if(frame_skill / (BOSS_SKILL2*2) >= BOSS_SKILL2)
                {
                    frame_skill = 0;
                    lightning = false;
                }
            }


    }
}

bool boss::getAttackPlayer(){
    return attackPlayer;
}
