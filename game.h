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
    boss mBoss;
    menu mMenu;
    int gameState;
    reload mReload;
    SDL_Rect mTilesClip[256];
    SDL_Rect bloodClip;
    SDL_Texture* mTexture[TOTAL_TEXTURE];
    bool on_ground;
    SDL_Rect camera;
    bool check_ball;
    int damage;
    int cnt;
    int random_enemy;
    std::vector<monster> mMonster;
    std::vector<wizard> mWizard;

    bool is_menu;
    bool is_play;

public:
    commom();
    ~commom();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkInit();
    bool checkLoadFile();
    void createTilesClip();
    void handlePlayer(SDL_Event &e);

    void setCamera();
    void setEnemy();
    void render();

    int getGameState();
    void endGame();
};

#endif // GAME_H
