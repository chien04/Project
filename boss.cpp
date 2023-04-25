#include "boss.h"

boss::boss()
{
    boxBoss = {17088, 0, BOSS_WIDTH, BOSS_HEIGHT};
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
    frame_death = 0;
    random_posX = boxBoss.x;
    random_enemy = 0;
    ban = false;
    lightning = false;
    isIdle = false;
    isRunning = false;
    isAttacking = false;
    attackPlayer = false;
    isTakeHit = false;
    isDeath = false;
    hp = 25;
    res = 0;
    lightningPosX = 0;
    lightningBox = {0, 0, 128, 256};
    createClip();
    cnt = 0;

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
        bossIdle[i] = {sum, 48, 272, 336};
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
        bossAttack2[i] = {sum, 1680, 352, 528};
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

    sum = 0;
    for(int i = 0; i < BOSS_TAKEHIT; i++){
        bossTakeHit[i] = {sum, 4208, 288, 336};
        sum += 304;
    }

    sum = 0;
    for(int i = BOSS_HP - 1; i >= 0; i--){
        bossHP[i] = {0, sum, 400, 32};
        sum += 48;
    }
    sum = 64;
    for(int i = 0; i < BOSS_DEATH; i++){
        bossDeath[i] = {sum, 4992, 288, 320};
        sum += 480;
    }
}

void boss::setPosX()
{
    posX = boxBoss.x;
}

void boss::setTotal_damage(){
    total_damage = 0;
}
void boss::move(tile tiles[], player mPlayer)
{
    if(isDeath)
        return;
    for(int i = 0; i < mMonster.size(); i++)
        mMonster[i].move(mPlayer, tiles);
    for(int i = 0; i < mWizard.size(); i++)
        mWizard[i].move(mPlayer, tiles);

//    std::cout << mMonster.size() << " " << mWizard.size() << std::endl;
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
            isRunning = false;
        }
    }

    if(isTakeHit)
        return;
//    if(ban) {
//        std::cout << "k ";
//        if(!isAttacking){
//            std::cout << "kkk\n";
//            isIdle = true;
//            return;
//        }
//    }
    if(isAttacking){
        if(boxBoss.x > mPlayer.getPosX())
            flip = SDL_FLIP_HORIZONTAL;
        else
            flip = SDL_FLIP_NONE;
        return;
    }


    SDL_Rect boxAttack = {posX - 500, boxBoss.y, 1000, BOSS_HEIGHT};

    if(checkCollision(boxAttack, mPlayer.getBox())){
        std::cout << "ccc ";
        if(!isAttacking){
            std::cout << "cc\n";
            isRunning = true;
            isIdle = false;
        }
    }
    if(isRunning){

        if(boxBoss.x < random_posX){
            flip = SDL_FLIP_NONE;
            boxBoss.x += velX;
        }
        if(boxBoss.x > random_posX){
            flip = SDL_FLIP_HORIZONTAL;
            boxBoss.x -= velX;
        }
        if(boxBoss.x == random_posX){
            cnt++;
            setPosX();
            random_posX = rand() % (17588- 16588 + 1) + 16588;
            random_posX = random_posX - (random_posX % velX) + (boxBoss.x % velX);
            isRunning = false;
            isAttacking = true;
            std::cout << boxBoss.x << " " << random_posX << std::endl;

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
    SDL_Rect ba = {posX - 500 - camera.x , boxBoss.y - camera.y, 1000, BOSS_HEIGHT};
    mWindow.renderBox(ba);
    if(isDeath)
        return;
    if(!ban)
    {
        flip_ball = flip;
    }
    for(int i = 0; i < BOSS_HP; i++){
        if(i == hp)
            mWindow.render(mTexture[BOSS_HP_TEXTURE], boxBoss.x - camera.x - 64, boxBoss.y - camera.y,
                           &bossHP[i], 0, NULL, SDL_FLIP_NONE, 300, 20);
    }
    if(hp > 0)
    {
        if(isRunning)
        {
            mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                           &bossRun[frame_run / BOSS_RUNNING], 0, NULL, flip, BOSS_WIDTH*16/17, BOSS_HEIGHT*19/21);
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
                           &bossTakeHit[frame_takehit / (BOSS_TAKEHIT * 4)], 0, NULL, flip, BOSS_WIDTH*(18/17), BOSS_HEIGHT);
            frame_takehit++;
            if(frame_takehit / (BOSS_TAKEHIT * 4) >= BOSS_TAKEHIT)
            {
                hp--;
                if(hp < 0)
                    hp = 0;
                frame_takehit = 0;
                isTakeHit = false;
                boxBoss.x = random_posX;
                frame_attack1 = 0;
                frame_attack2 = 0;
                mBall.clear();
            }
        }
        if(isAttacking)
        {
            if(res == 0){
                mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y + 12,
                           &bossAttack1[frame_attack1 / BOSS_ATTACK1], 0, NULL, flip, BOSS_WIDTH *(20/17), BOSS_HEIGHT);
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
                    if(mBall.size() != 0)
                        ban = true;
                }
                if(frame_attack1 / (BOSS_ATTACK1) >= BOSS_ATTACK1)
                {
                    res = rand() % 2;
                    isAttacking = false;
                    frame_attack1 = 0;
                }
            }
            if(res == 1){
                mWindow.render(mTexture[BOSS_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y - 120,
                               &bossAttack2[frame_attack2 / BOSS_ATTACK2], 0, NULL, flip, BOSS_WIDTH*22/17, BOSS_HEIGHT*11/7);
                frame_attack2++;
                if(frame_attack2 / BOSS_ATTACK2 == 9)
                    lightning = true;
                if(frame_attack2 / BOSS_ATTACK2 >= BOSS_ATTACK2)
                {
                    res = rand() % 2;
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
                    if(mBall[i].getAttackPlayer()) {
                        attackPlayer = true;
                        total_damage++;
                    }
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
                mWindow.render(mTexture[WIZARD_TEXTURE], lightningPosX - 12 - camera.x, boxBoss.y - camera.y,
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

        if(cnt == 3){
            random_enemy = rand() % 2;
            if(random_enemy == 0)
                mMonster.push_back(monster(boxBoss.x, 0));
            if(random_enemy == 1)
                mWizard.push_back(wizard(boxBoss.x , 0));
            cnt = 0;
        }
        for(int i = 0; i < mMonster.size(); i++){
            mMonster[i].render(mWindow, camera, mTexture, mplayer);
            if(mMonster[i].getMonsterAttack())
                total_damage++;
            if(mMonster[i].getDeath())
                mMonster.erase(mMonster.begin() + i);
        }
        for(int i = 0; i < mWizard.size(); i++){
            mWizard[i].render(mWindow, camera, mTexture, mplayer);
            if(mWizard[i].getAttackPlayer())
                total_damage++;
            if(mWizard[i].getDeath())
                mWizard.erase(mWizard.begin() + i);
        }


    }
    if(hp == 0){
         mWindow.render(mTexture[WIZARD_TEXTURE], boxBoss.x - camera.x, boxBoss.y - camera.y,
                               &bossDeath[frame_death / (BOSS_DEATH * 4)], 0, NULL, flip, BOSS_WIDTH * 18/17, BOSS_HEIGHT * 20/21);
        frame_death++;
        if(frame_death / (BOSS_DEATH * 4) >= BOSS_DEATH){
            frame_death = 0;
            isDeath = true;
        }
    }
}

bool boss::getAttackPlayer(){
    return attackPlayer;
}

int boss::getTotal_damage(){
    return total_damage;
}
