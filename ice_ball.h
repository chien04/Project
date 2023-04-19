
#ifndef ICE_BALL_H
#define ICE_BALL_H
#include "base.h"
#include "tile_map.h"
class ice_ball{

public:
    ice_ball();
    ice_ball(SDL_Rect box, SDL_RendererFlip flip);
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool touchesWall(SDL_Rect boxBall, tile tiles[]);
    void move(SDL_RendererFlip flip, SDL_Rect boxPlayer);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]);
    bool getBan();
    bool getAttackPlayer();
    SDL_Rect getBoxBall();

private:
    SDL_Rect boxBall;
    SDL_Rect boxBallClip;
    int initialPosX;
    bool isBan;
    bool attackPlayer;
};


class fire_ball: public ice_ball{
public:
    fire_ball();
    fire_ball(SDL_Rect box, SDL_RendererFlip flip);
    void move(SDL_RendererFlip flip, SDL_Rect boxPlayer);
    void render(createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[]);
    bool getBan();
    bool getAttackPlayer();
    SDL_Rect getBoxBall();

private:
    SDL_Rect boxBall;
    SDL_Rect boxBallClip;
    int initialPosX;
    bool isBan;
    bool attackPlayer;
};
#endif // ICE_BALL_H
