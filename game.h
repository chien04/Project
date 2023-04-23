#ifndef GAME_H
#define GAME_H

#include "base.h"
#include "tile_map.h"
#include "base.h"
#include "hangso_const.h"
#include "player.h"
#include "monster.h"
#include "wizard.h"
#include "boss.h"
#include "menu.h"
class commom{
private:

    createWindow mWindow;
    tile mtile[TOTAL_TILES];
    gameMap mMap;
    player mPlayer;
//    monster mMonster[TOTAL_MONSTER];
//    wizard mWizard[TOTAL_WIZARD];
    boss mBoss;
    reload mReload;
    SDL_Rect mTilesClip[256];
    SDL_Rect bloodClip;
    SDL_Texture* mTexture[TOTAL_TEXTURE];
    bool on_ground;
    SDL_Rect camera;
    bool check_ball;
    int damage;
    std::vector<monster> mMonster;
    std::vector<wizard> mWizard;
public:
    commom();
    ~commom();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkInit();
    bool checkLoadFile();
    void createTilesClip();
    void handlePlayer(SDL_Event &e);

    void setCamera();

    void render();

    void endGame();
};

#endif // GAME_H
