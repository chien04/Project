#include <vector>
#include "monster.h"


bool checkCollision( SDL_Rect a, SDL_Rect b )
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


monster::monster(int x, int y)
{
    velX = MONSTER_VEL_X;
    velY = MONSTER_VEL_Y;
    flip = SDL_FLIP_NONE;
    createMonsterClip();
    for(int i = 0; i < TOTAL_FRAME; i++)
    {
        frame[i] = 0;
    }
    on_ground = false;
    boxMonster = {x, y, MONSTER_WIDTH, MONSTER_HEIGHT};
    isIdle = false;
    isRunning = true;
    isAttacking = false;
    isHitting = false;
    attackPlayer = false;

    is_death = false;
    hp = 6;
    cnt = 120;
}

void monster::createMonsterClip()
{
    int sum = 0;
    for(int i = 0; i < MONSTER_IDLE; i++)
    {
        monsterIdle[i] = {sum, 0, 80, 96};
        sum += 96;
    }
    sum = 0;
    for(int i = 0; i < MONSTER_RUN; i++)
    {
        monsterRun[i] = {sum, 176, 96, 96};
        sum += 112;
    }
    sum = 0;
    for(int i = 0; i < MONSTER_ATTACK; i++)
    {
        monsterAttack[i] = {sum, 368, 160, 128};
        sum += 176;
    }
    sum = 0;
    for(int i = 0; i < MONSTER_KNOCKBACK; i++)
    {
        monsterKnockBack[i] = {sum, 752, 80, 96};
        sum += 96;
    }
    sum = 0;

    for(int i = 0; i < MONSTER_DEATH; i++)
    {
        monsterDeath[i] = {sum, 576, 112, 80};
        sum += 128;
    }
}

bool monster::checkCollision( SDL_Rect a, SDL_Rect b )
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
bool monster::touchesWall( SDL_Rect boxMonster, tile tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if(tiles[ i ].getTileType() != -1)
        {
            //If the collision box touches the wall tile
            if( checkCollision( boxMonster, tiles[ i ].getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void monster::move(player mPlayer, tile tiles[], int pos_x)
{
    if(checkCollision(boxMonster, mPlayer.getBox()))
    {
        isRunning = false;
        if(mPlayer.getIsttacking())
        {
            isHitting = true;
            hp--;
            if(hp < 0)
                hp = 0;
        }
        else
        {
            if(cnt < 120){
                isIdle = true;
                return;
            }

            if(cnt >= 120 && cnt <= 227)
                isAttacking = true;
            if(frame[FRAME_ATTACK] == 54)
                attackPlayer = true;
            else
                attackPlayer = false;
//            std::cout << frame[FRAME_ATTACK] << std::endl;
//            std::cout << attackPlayer << std::endl;
            if(!attackPlayer)
                return;
        }
        if(boxMonster.x > mPlayer.getPosX())
            {
                if(flip == SDL_FLIP_NONE)
                {
                    flip = SDL_FLIP_HORIZONTAL;
                    velX *= -1;
                }
            }
            else
            {
                if(flip == SDL_FLIP_HORIZONTAL)
                {
                    flip = SDL_FLIP_NONE;
                    velX *= -1;
                }
            }


    }
    if(!checkCollision(boxMonster, mPlayer.getBox()))
    {

        if(isRunning == false)
            return ;
        isRunning = true;

        isIdle = false;
        boxMonster.x += velX;
        if(boxMonster.x >= pos_x + 200)
        {
            velX *= -1;
            flip = SDL_FLIP_HORIZONTAL;
        }
        if(boxMonster.x <= pos_x - 200)
        {
            velX *= -1;
            flip = SDL_FLIP_NONE;
        }
        boxMonster.y += velY;
        if(touchesWall(boxMonster, tiles))
        {
            boxMonster.y -= velY;
        }
    }

}

void monster::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], player mPlayer)
{
    if(is_death)
        return;
    if(hp > 0)
    {
        if(isRunning)
        {
            mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x, boxMonster.y - camera.y,
                           &monsterRun[frame[FRAME_RUN]/(MONSTER_RUN)], 0, NULL, flip, MONSTER_WIDTH, MONSTER_HEIGHT);
            frame[FRAME_RUN]++;
            if(frame[FRAME_RUN]/( MONSTER_RUN) >=  MONSTER_RUN)
            {
                frame[FRAME_RUN] = 0;
            }
        }
        if(isAttacking == true)
        {
            isIdle = false;
            if(flip == SDL_FLIP_NONE)
            mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x, boxMonster.y - camera.y - 32,
                           &monsterAttack[frame[FRAME_ATTACK]/(MONSTER_ATTACK*3)], 0, NULL, flip, (double)(MONSTER_WIDTH*5)/3, (double)(MONSTER_HEIGHT)*4/3);
            else
                mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x - 48, boxMonster.y - camera.y - 32,
                           &monsterAttack[frame[FRAME_ATTACK]/(MONSTER_ATTACK*3)], 0, NULL, flip, (double)(MONSTER_WIDTH*5)/3, (double)(MONSTER_HEIGHT)*4/3);
            frame[FRAME_ATTACK]++;

            if(frame[FRAME_ATTACK] / (MONSTER_ATTACK * 3) >= MONSTER_ATTACK)
            {
                frame[FRAME_ATTACK] = 0;
                isAttacking = false;
                isRunning = true;
            }
        }
        if(isHitting == true)
        {
            isAttacking = false;
            if(boxMonster.x > mPlayer.getPosX())
            {
                boxMonster.x += 3;
            }
            else
            {
                boxMonster.x -= 3;
            }
            mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x, boxMonster.y - camera.y,
                           &monsterKnockBack[frame[FRAME_KNOCKBACK]/ (MONSTER_KNOCKBACK*30)], 0, NULL, flip, MONSTER_WIDTH, MONSTER_HEIGHT);
            frame[FRAME_KNOCKBACK]++;
            if(frame[FRAME_KNOCKBACK] / (MONSTER_KNOCKBACK*30) >= MONSTER_KNOCKBACK)
            {
                frame[FRAME_KNOCKBACK] = 0;
                isRunning = false;
                isHitting = false;
                isAttacking = false;
                isIdle = true;
                frame[FRAME_ATTACK] = 0;

            }
            cnt = 0;
        }
        if(isIdle)
        {
            mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x, boxMonster.y - camera.y,
                           &monsterIdle[frame[FRAME_IDLE] / (MONSTER_IDLE*16)], 0, NULL, flip, MONSTER_WIDTH, MONSTER_HEIGHT);
            frame[FRAME_IDLE]++;
            if(frame[FRAME_IDLE] / (MONSTER_IDLE*16) >= MONSTER_IDLE)
            {
                frame[FRAME_IDLE] = 0;
                isRunning = true;
            }
        }
    }
    if(hp == 0)
    {
        mWindow.render(mTexture[MONSTER_TEXTURE], boxMonster.x - camera.x, boxMonster.y - camera.y,
                       &monsterDeath[frame[FRAME_DEATH] / (MONSTER_DEATH * 20)], 0, NULL, flip, MONSTER_WIDTH*4/3, MONSTER_HEIGHT - 16);
        frame[FRAME_DEATH]++;
        if(frame[FRAME_DEATH] / (MONSTER_DEATH* 20) >= MONSTER_DEATH)
        {
            frame[FRAME_DEATH] = 0;
            is_death = true;
        }

    }
    cnt++;
    if(cnt > 227)
    {
        cnt = 0;
    }
    if(isRunning)
        cnt = 120;

}

int monster::getPosX()
{
    return boxMonster.x;
}

bool monster::getMonsterAttack(){
    return attackPlayer;
}
