#ifndef GAME_H
#define GAME_H

#include "sstream"
#include "base.h"
#include "tile_map.h"
#include "base.h"
#include "hangso_const.h"
#include "player.h"
#include "monster.h"
#include "wizard.h"
#include "boss.h"
#include "menu.h"
class common{
private:

    createWindow mWindow;
    tile mtile[TOTAL_TILES];
    gameMap mMap;
    player mPlayer;
    boss mBoss;
    menu mMenu;
    guide mGuide;
    int gameStateMenu;
    int gameStateGuide;
    int gameStateReload;
    int gameStatePause;
    int gameStateWin;
    reload mReload;
    pause mPause;
    won mWon;
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
    bool dd[10005];
    bool is_menu;
    bool is_play;
    bool is_guide;
    bool restart;
    Mix_Chunk *gameSound[TOTAL_SOUND];
    Mix_Music *gameMusic[TOTAL_MUSIC];
    bool tmp1;
    bool tmp2;
    int score;
    TTF_Font *mFont;
    TTF_Font *fontArial;
    std::stringstream scoreText;
    std::stringstream iTemHp;
    std::stringstream iTemExp;


public:
    common();
    ~common();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkInit();
    bool checkLoadFile();
    bool checkLoadFont();
    bool checkLoadSound();
    void createTilesClip();
    void handlePlayer(SDL_Event &e);

    void setCamera();
    void setEnemy();
    void render();
    void renderScore();
    int getGameState();
    void endGame();
};

#endif // GAME_H
