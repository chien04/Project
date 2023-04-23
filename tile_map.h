#ifndef TILEMAP_H
#define TILEMAP_H

#include "base.h"
#include "hangso_const.h"

class tile{
public:
    tile(int x_position = 0, int y_position = 0, int tile_type = 0);
    void render();

    int getTileType();
    int getX_position();
    int getY_position();
    SDL_Rect getBox();
private:
    SDL_Rect mBoxTile;
    int mType;

};

class gameMap
{
public:
    gameMap();
    bool loadMap( tile tiles[]);
    void renderMap(int velX, SDL_RendererFlip flip, createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[], tile tiles[], SDL_Rect mTilesClip[]);
private:
    int x_coordinate;
    int y_coordinate;
    double scrolling;
    double scrolling_middle;
};

#endif // TILEMAP_H
