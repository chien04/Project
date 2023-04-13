#include "wizard.h"


wizard::wizard(int x, int y)
{
    velX = 0;
    velY = MONSTER_VEL_Y;

    flip = SDL_FLIP_NONE;
    flip_ball = SDL_FLIP_NONE;
    createWizardClip();

    for(int i = 0; i < WIZARD_FRAME; i++)
    {
        frame[i] = 0;
    }
    inZone = false;
    isAttacking = false;
    isDeath = false;
    boxWizard = {x, y, WIZARD_WIDTH, WIZARD_HEIGHT};
    ban = false;
    cnt = 0;
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
        wizardTakeHit[i] = {0, 160, 48, 48};
        sum += 48;
    }
    for(int i = 0; i < WIZARD_DEATH; i++)
    {
        wizardDeath[i] = {0, 240, 64, 48};
        sum += 64;
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
//    printf("%d %d %d %d\n", leftB, rightB, topB, bottomB);
//    printf("%d %d %d %d\n", leftA, rightA, topA, bottomA);

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool wizard::touchesWall( SDL_Rect boxWizard, tile tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if(tiles[ i ].getTileType() != -1)
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

void wizard::move(player mPlayer, tile tiles[], int pos_x)
{
    if(isDeath)
        return;
    if(isAttacking)
        return;
    boxWizard.x = pos_x;
    boxWizard.y += velY;
    if(touchesWall(boxWizard, tiles))
    {
        boxWizard.y -= velY;
    }

    if(abs(mPlayer.getPosX() - pos_x) < 350)
    {
        inZone = true;
    }
    else
    {
        inZone = false;
        frame[ATTACK] = 0;
    }
    if(boxWizard.x > mPlayer.getPosX())
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

}

void wizard::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mplayer)
{
    if(isDeath)
        return;
    if(!ban)
        flip_ball = flip;
    if(inZone == false || (cnt < 91 && inZone == true))
    {
        mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x, boxWizard.y - camera.y,
                       &wizardIdle[frame[IDLE]/WIZARD_IDLE], 0, NULL, flip, WIZARD_WIDTH, WIZARD_HEIGHT);

        frame[IDLE]++;
        if(frame[IDLE] / WIZARD_IDLE >= WIZARD_IDLE)
            frame[IDLE] = 0;
    }
    if(inZone == true && cnt >= 91)
    {
        isAttacking = true;
        if(flip == SDL_FLIP_NONE)
            mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 32, boxWizard.y - camera.y,
                           &wizardAttack[frame[ATTACK]/(WIZARD_ATTACK*2)], 0, NULL, flip, WIZARD_WIDTH*5/2, WIZARD_HEIGHT);
        else if(flip == SDL_FLIP_HORIZONTAL)
            mWindow.render(mTexture[WIZARD_TEXTURE], boxWizard.x - camera.x - 64, boxWizard.y - camera.y,
                           &wizardAttack[frame[ATTACK]/(WIZARD_ATTACK*2)], 0, NULL, flip, WIZARD_WIDTH*5/2, WIZARD_HEIGHT);
        if(mBall.size() == 0)
        {
            mBall.push_back(ice_ball(boxWizard, flip_ball));
        }

        frame[ATTACK]++;
        if(frame[ATTACK]/(WIZARD_ATTACK*2) == 7 )
        {
            ban = true;
        }
        if(frame[ATTACK] / (WIZARD_ATTACK*2) >= WIZARD_ATTACK)
        {
            isAttacking = false;
            frame[ATTACK] = 0;
            cnt = 0;
        }
    }
    for(int i = 0; i < mBall.size(); i++)
    {
        if(ban)
        {
            mBall[i].move(flip_ball);
        }
    }

    if(ban)
    {
        for(int i = 0; i < mBall.size(); i++)
        {
            if(mBall[i].getBan())
            {
                mBall[i].render(mWindow, camera, mTexture);
            }
            else
            {
                mBall.erase(mBall.begin() + i);
                ban = false;
            }
        }
    }
    cnt++;


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


