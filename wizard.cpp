#include "wizard.h"


wizard::wizard(int x, int y)
{
    velX = 0;
    velY = MONSTER_VEL_Y;

    pos_x = x;
    flip = SDL_FLIP_NONE;
    flip_ball = SDL_FLIP_NONE;
    createWizardClip();

    for(int i = 0; i < WIZARD_FRAME; i++)
    {
        frame[i] = 0;
    }
    inZone = false;
    isAttacking = false;
    isHitting = false;
    take_hit = false;
    attackPlayer = false;
    isDeath = false;
    boxWizard = {x, y, WIZARD_WIDTH, WIZARD_HEIGHT};
    ban = false;
    cnt = 0;
    hp = 3;
}

void wizard::createWizardClip()
{
    int sum = 0;
    for(int i = 0; i < WIZARD_IDLE; i++)
    {
        wizardIdle[i] = {sum, 0, 32, 48};
        sum += 32;
    }
    sum = 0;
    for(int i = 0; i < WIZARD_ATTACK; i++)
    {
        wizardAttack[i] = {sum, 80, 80, 48};
        sum += 80;
    }
    sum = 0;
    for(int i = 0; i < WIZARD_TAKE_HIT; i++)
    {
        wizardTakeHit[i] = {sum, 160, 48, 48};
        sum += 48;
    }
    for(int i = 0; i < WIZARD_DEATH; i++)
    {
        wizardDeath[i] = {sum, 240, 64, 48};
        sum += 64;
    }
    sum = 144;
    for(int i = WIZARD_HP - 1; i >= 0; i--)
    {
        wizardHP[i] = {0, sum, 128, 16};
        sum += 32;
    }
}
//
bool wizard::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
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
    //If none of the sides from A are outside B
    return true;
}

bool wizard::checkCollisionTrap(SDL_Rect a, SDL_Rect b)
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
bool wizard::touchesWall( SDL_Rect boxWizard, tile tiles[] )
{
    //Go through the tiles
    std::set<int> mySet;
    mySet.insert(-1);
    for(int i = 0; i < 30; i++){
        mySet.insert(i);
    }
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if(tiles[i].getTileType() == 12 || tiles[i].getTileType() == 13){
            if(checkCollisionTrap(boxWizard, tiles[i].getBox())){
                hp = 0;
            }
        }
        //If the tile is a wall type tile
        if(!mySet.count(tiles[ i ].getTileType()))
        {
            //If the collision box touches the wall tile
            if( checkCollision( boxWizard, tiles[ i ].getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void wizard::move(player mPlayer, tile tiles[])
{
    if(isDeath)
        return;
    boxWizard.y += velY;
    if(touchesWall(boxWizard, tiles))
    {
        boxWizard.y -= velY;
    }
    if(checkCollision(boxWizard, mPlayer.getBoxShot())){
        if(mPlayer.getAttackMonsterByShot())
            hp = 0;
    }

    if(isHitting){
        if(boxWizard.x > mPlayer.getPosX()){
            boxWizard.x += 1;
            if(touchesWall(boxWizard, tiles))
                boxWizard.x -= 1;
        }
        else{
            boxWizard.x -= 1;
            if(touchesWall(boxWizard, tiles))
                boxWizard.x += 1;
        }

    }
    take_hit = false;
    if(checkCollision(mPlayer.getBox(), boxWizard))
    {
        if(mPlayer.getIsttacking())
        {
            isHitting = true;
            take_hit = true;
            isAttacking = false;
            hp--;
            if(hp < 0)
                hp = 0;
        }
    }
    if(isAttacking)
        return;
    if(boxWizard.x > mPlayer.getPosX())
    {
        if(flip == SDL_FLIP_NONE)
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
    }
    else
    {
        if(flip == SDL_FLIP_HORIZONTAL)
        {
            flip = SDL_FLIP_NONE;
        }
    }
    if(abs(mPlayer.getPosX() - pos_x) < 350)
    {
        inZone = true;
        isAttacking = true;
    }
    else
    {
        inZone = false;
//        frame[ATTACK] = 0;
    }
}

void wizard::setPosX()
{
    if(isHitting)
        pos_x = boxWizard.x - 32;
}
void wizard::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mplayer)
{
    if(isDeath)
        return;
    if(!ban)
        flip_ball = flip;
    if(hp > 0)
    {
        if(inZone == false || (cnt < 120 && inZone == true))
        {
            mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x, boxWizard.y - camera.y,
                           &wizardIdle[frame[IDLE]/WIZARD_IDLE], 0, NULL, flip, WIZARD_WIDTH, WIZARD_HEIGHT);

            frame[IDLE]++;
            if(frame[IDLE] / WIZARD_IDLE >= WIZARD_IDLE)
                frame[IDLE] = 0;
        }
        if(inZone)
        {
            if(isHitting)
            {
                mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 32, boxWizard.y - camera.y,
                               &wizardTakeHit[frame[TAKE_HIT]/(WIZARD_TAKE_HIT*5)], 0, NULL, flip, WIZARD_WIDTH*3/2, WIZARD_HEIGHT);
                frame[TAKE_HIT]++;
                if(frame[TAKE_HIT] / (WIZARD_TAKE_HIT*5) >= WIZARD_TAKE_HIT)
                {
                    frame[TAKE_HIT] = 0;
                    isHitting = false;
                    isAttacking = true;
                    frame[ATTACK] = 0;
                }
            }
        }
        if(inZone == true && cnt >= 120 && isHitting == false)
        {

            if(isAttacking)
            {
                if(flip == SDL_FLIP_NONE)
                    mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 32, boxWizard.y - camera.y,
                                   &wizardAttack[frame[ATTACK]/(WIZARD_ATTACK*2)], 0, NULL, flip, WIZARD_WIDTH*5/2, WIZARD_HEIGHT);
                else if(flip == SDL_FLIP_HORIZONTAL)
                    mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 64, boxWizard.y - camera.y,
                                   &wizardAttack[frame[ATTACK]/(WIZARD_ATTACK*2)], 0, NULL, flip, WIZARD_WIDTH*5/2, WIZARD_HEIGHT);
                if(mBall.size() == 0 && frame[ATTACK] == 0)
                {
                    mBall.push_back(ice_ball(boxWizard, flip_ball));
                }

                frame[ATTACK]++;
                if(frame[ATTACK]/(WIZARD_ATTACK*2) == 7 )
                {
                    if(mBall.size() != 0)
                        ban = true;
                }
                if(frame[ATTACK] / (WIZARD_ATTACK*2) >= WIZARD_ATTACK)
                {
                    isAttacking = false;
                    frame[ATTACK] = 0;
                    cnt = 0;
                }
            }
        }

        if(ban)
        {
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
//                mBall[i].setAttackPlayer();
                if(mBall[i].getAttackPlayer())
                    attackPlayer = true;
                else
                    attackPlayer = false;
            }
        }
        else
            attackPlayer = false;
        cnt++;

        if(flip == SDL_FLIP_NONE)
        {
            for(int i = 0; i < WIZARD_HP; i++)
            {
                if(i == hp)
                    mWindow.render(mTexture[HP_ENEMY_TEXTURE], boxWizard.x - camera.x + 10, boxWizard.y - camera.y - 15,
                        &wizardHP[i], 0, NULL, flip, 48, 6);
            }
        }
        else if(flip == SDL_FLIP_HORIZONTAL)
        {
            for(int i = 0; i < WIZARD_HP; i++)
            {
                if(i == hp)
                    mWindow.render(mTexture[HP_ENEMY_TEXTURE], boxWizard.x - camera.x + 20, boxWizard.y - camera.y - 15,
                        &wizardHP[i], 0, NULL, flip, 48, 6);
            }
        }
    }


    if(hp == 0)
    {
        mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 32, boxWizard.y - camera.y,
                       &wizardDeath[frame[DEATH]/(WIZARD_DEATH*2)], 0, NULL, flip, WIZARD_WIDTH*5/2, WIZARD_HEIGHT);
        frame[DEATH]++;
        if(frame[DEATH] / (WIZARD_DEATH*2) >= WIZARD_DEATH)
        {
            frame[DEATH] = 0;
            isDeath = true;
        }
    }

}

int wizard::getPosX()
{
    return boxWizard.x;
}
int wizard::getPosY()
{
    return boxWizard.y;
}

bool wizard::getBan()
{
    return ban;
}

SDL_Rect wizard::getBoxWizard()
{
    return boxWizard;
}

bool wizard::getIsTakeHit(){
    return take_hit;
}

bool wizard::getAttackPlayer()
{
    return attackPlayer;
}

bool wizard::getDeath(){
    return isDeath;
}
