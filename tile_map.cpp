#include "tile_map.h"
#include "base.h"
#include <fstream>
#include "player.h"

tile::tile(int x_position, int y_position, int tile_type){
    mBoxTile.x = x_position;
    mBoxTile.y = y_position;

    mBoxTile.w = TILE_WIDTH;
    mBoxTile.h = TILE_HEIGHT;
    mType = tile_type;

}

int tile::getTileType(){
    return mType;
}

int tile::getX_position(){
    return mBoxTile.x;
}
int tile::getY_position(){
    return mBoxTile.y;
}

SDL_Rect tile::getBox(){
    return mBoxTile;
}

gameMap::gameMap(){
    x_coordinate = 0;
    y_coordinate = 0;
}

bool gameMap::loadMap( tile tiles[]){
    bool success = true;
    std::ifstream map_game("map//nit.txt");
    if(map_game.fail()){
        success = false;
        std::cout << "unable to load map\n";
    }

    else{
        for(int i = 0; i < TOTAL_TILES; i++){
            int tileType = -1;
            map_game >> tileType;
                tiles[i] = tile(x_coordinate, y_coordinate, tileType);

            x_coordinate += TILE_WIDTH;
            if(x_coordinate >= WIDTH_MAP){
                x_coordinate = 0;
                y_coordinate += TILE_HEIGHT;
            }
        }
    }
    map_game.close();

    return success;
}

void gameMap::renderMap(int velX, SDL_RendererFlip flip, createWindow mWindow, SDL_Rect camera, SDL_Texture* mTexture[],tile tiles[], SDL_Rect mTilesClip[]){


    mWindow.render(mTexture[BACKGROUND_TEXTURE], 0, 0, NULL, 0, NULL, SDL_FLIP_NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i = 0; i < TOTAL_TILES; i++){
        int x = tiles[i].getX_position();
        int y = tiles[i].getY_position();
        int tilesClip = tiles[i].getTileType();

        if(tilesClip != -1)
        {
            mWindow.render(mTexture[MAP_TEXTURE], x - camera.x, y - camera.y, &mTilesClip[tilesClip], 0, NULL, SDL_FLIP_NONE, TILE_WIDTH, TILE_HEIGHT);

        }
    }

}


