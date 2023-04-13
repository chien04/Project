#ifndef GAME_H
#define GAME_H

#include "base.h"
#include "tile_map.h"
#include "base.h"
#include "hangso_const.h"
#include "player.h"
#include "monster.h"
#include "wizard.h"
class commom{
private:

    createWindow mWindow;
    tile mtile[TOTAL_TILES];
    gameMap mMap;
    player mPlayer;
    monster mMonster[TOTAL_MONSTER];
    wizard mWizard[TOTAL_WIZARD];
    SDL_Rect mTilesClip[256];

    SDL_Texture* mTexture[TOTAL_TEXTURE];
    bool on_ground;
    SDL_Rect camera;
    int posX_monster[TOTAL_MONSTER];
    int posX_wizard[TOTAL_WIZARD];
    bool check;
public:
    commom();
    ~commom();

    bool checkInit();
    bool checkLoadFile();
    void createTilesClip();
    void handlePlayer(SDL_Event &e);

    void setCamera();

    void render();

    void endGame();
};

#endif // GAME_H
