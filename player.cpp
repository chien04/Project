#include "player.h"
#include "game.h"
#include "hangso_const.h"
#include <time.h>
#include <stdlib.h>
#include "monster.h"
player::player()
{
    cnt_jump = 0;
    boxPlayer.x = 0;
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
    on_ground = false;
    isIdle = false;
    isRunning = false;
    isJump = false;
    attacking = false;
    attackMonster = false;
    isTakeHit = false;
    isDeath = false;
    createPlayerClip();
    createEffectTexture();
    hp = 5;
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
        mPlayerJump[i] = {sum, 288, 64, 67};
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
}

void player::createEffectTexture()
{
    int sum = 0;
    int sum1 = 0;
    for(int i = 0; i < EFFECT_CLIP; i++)
    {
        mEffectClip[i] = {sum, sum1, 192, 192};
        sum += 192;
        if(sum >= 2304)
        {
            sum = 0;
            sum1 += 192;
        }
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
            if(on_ground)
            {
                velY = -PLAYER_VEL;
                on_ground = false;
                cnt_jump = 0;
            }
            break;
        case SDLK_a:
            if(attacking == false)
            {
                attacking = true;
            }
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
bool player::touchesWall( SDL_Rect boxPlayer, tile tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if(tiles[ i ].getTileType() != -1)
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

    if(velX < 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if(velX > 0)
    {
        flip = SDL_FLIP_NONE;
    }
    if(velX == 0 && on_ground == true && attacking == false)
    {
        isIdle = true;
        isRunning = false;
        isJump = false;
    }
    if(velX != 0 && on_ground == true && attacking == false)
    {
        isIdle = false;
        isRunning = true;
        isJump = false;
    }
    if(on_ground == false && attacking == false)
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
    }

}
void player::setIsTakeHit(bool x, bool y)
{
    if(x == false && y == false)
        isTakeHit = false;
    else
        isTakeHit = true;

}

bool player::isTakeHitByMonster()
{
    return isTakeHit;
}
void player::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[])
{
    for(int i = 0; i < PLAYER_HEALTH; i++)
    {
        if(i == hp)
            mWindow.render(mTexture[HEALTH_TEXTURE], 10, 30,
                           &mPlayeHeath[i], 0, NULL, SDL_FLIP_NONE, 210, 70);
    }
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
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 24, boxPlayer.y - camera.y - 24,
                               &mPlayerJump[frame/PLAYER_JUMP], 0, NULL, flip, PLAYER_WIDTH_JUMP, PLAYER_HEIGHT_JUMP);
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
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 48, boxPlayer.y - camera.y - 48,
                                   &mPlayerAttack[frame_attack/PLAYER_ATTACK], 0, NULL, flip, PLAYER_WIDTH_ATTACK, PLAYER_HEIGHT_ATTACK);
                }
                else if(flip == SDL_FLIP_NONE)
                {
                    mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 64, boxPlayer.y - camera.y - 48,
                                   &mPlayerAttack[frame_attack/PLAYER_ATTACK], 0, NULL, flip, PLAYER_WIDTH_ATTACK, PLAYER_HEIGHT_ATTACK);
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
        }
        else
        {
            if(flip == SDL_FLIP_NONE)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 204, boxPlayer.y - camera.y - 128,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*3)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
                frame_takehit++;
                if(frame_takehit / (PLAYER_TAKEHIT*3) >= PLAYER_TAKEHIT)
                {
                    frame_takehit = 0;
                    isTakeHit = false;
                    hp--;
                }
            }
            else if(flip == SDL_FLIP_HORIZONTAL)
            {
                mWindow.render(mTexture[PLAYER_TEXTURE], boxPlayer.x - camera.x - 308, boxPlayer.y - camera.y - 128,
                               &mPlayerTakeHit[frame_takehit/(PLAYER_TAKEHIT*3)], 0, NULL, flip, PLAYER_WIDTH*9, PLAYER_HEIGHT*10/3);
                frame_takehit++;
                if(frame_takehit / (PLAYER_TAKEHIT*3) >= PLAYER_TAKEHIT)
                {
                    frame_takehit = 0;
                    isTakeHit = false;
                    hp--;
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

bool player::getIsDeath(){
    return isDeath;
}
