#include "ice_ball.h"


bool ice_ball::checkCollision( SDL_Rect a, SDL_Rect b )
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
    return true;
}

bool ice_ball::touchesWall( SDL_Rect boxWizard, tile tiles[] )
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
ice_ball::ice_ball(){
    boxBall = {0,0,0,0};
    boxBallClip = {0, 0, 0, 0};
    isBan = false;
    attackPlayer = false;
}

ice_ball::ice_ball(SDL_Rect box, SDL_RendererFlip flip){
    if(flip == SDL_FLIP_NONE){
        boxBall = {box.x + 48, box.y + 64, 32, 32};
        initialPosX = boxBall.x;
    }
    else{
        boxBall = {box.x - 48, box.y + 64, 32, 32};
        initialPosX = boxBall.x;
    }

    boxBallClip = {0, 320, 16, 16};
    isBan = true;
    attackPlayer = false;
}

void ice_ball::move(SDL_RendererFlip flip, SDL_Rect boxPlayer){
    if(flip == SDL_FLIP_NONE){
        if(isBan) boxBall.x += BULLET_VEL;
    }
    if(flip == SDL_FLIP_HORIZONTAL){
        if(isBan) boxBall.x -= BULLET_VEL;
    }
    if(abs(initialPosX - boxBall.x) > 500) isBan = false;
    if(checkCollision(boxBall, boxPlayer)){
        attackPlayer = true;
        isBan = false;
    }
}
void ice_ball::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]){
    if(isBan) mWindow.render(mTexture[WIZARD_TEXTURE], boxBall.x - camera.x, boxBall.y - camera.y - 20,
                   &boxBallClip, 0, NULL, SDL_FLIP_HORIZONTAL, 32, 32);
}

bool ice_ball::getBan()
{
    return isBan;
}

SDL_Rect ice_ball::getBoxBall(){
    return boxBall;
}

bool ice_ball::getAttackPlayer(){
    return attackPlayer;
}


fire_ball::fire_ball(){
    boxBall = {0, 0, 32, 32};
    boxBallClip = {0, 384, 80, 96};
    initialPosX = 0;
    isBan = true;
    attackPlayer = false;
}

fire_ball::fire_ball(SDL_Rect box, SDL_RendererFlip flip){
    if(flip == SDL_FLIP_NONE){
        boxBall = {box.x + 48, box.y + 64, 32, 32};
        initialPosX = boxBall.x;
        std::cout << "NONE " << initialPosX << std::endl;
    }
    else{
        boxBall = {box.x - 48, box.y + 64, 32, 32};
        initialPosX = boxBall.x;
        std::cout << "HOZIRENTIAL " << initialPosX << std::endl;
    }

    boxBallClip = {0, 384, 80, 96};
    isBan = true;
    attackPlayer = false;
}

void fire_ball::move(SDL_RendererFlip flip, SDL_Rect boxPlayer){
    if(flip == SDL_FLIP_NONE){
        if(isBan) boxBall.x += BULLET_VEL;
    }
    if(flip == SDL_FLIP_HORIZONTAL){
        if(isBan) boxBall.x -= BULLET_VEL;
    }
    if(abs(initialPosX - boxBall.x) > 500) isBan = false;

    if(checkCollision(boxBall, boxPlayer)){
        attackPlayer = true;
        isBan = false;
    }
}
void fire_ball::render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]){
    if(isBan) mWindow.render(mTexture[WIZARD_TEXTURE], boxBall.x - camera.x, boxBall.y - camera.y ,
                   &boxBallClip, 0, NULL, SDL_FLIP_HORIZONTAL, 40, 48);
}

bool fire_ball::getBan()
{
    return isBan;
}

SDL_Rect fire_ball::getBoxBall(){
    return boxBall;
}

bool fire_ball::getAttackPlayer(){
    return attackPlayer;
}
