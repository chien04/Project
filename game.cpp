#include "game.h"

commom::commom(){

    gameState = -1;
    is_menu = true;
    is_play = false;
    mTexture[MAP_TEXTURE] = NULL;
    mMap.loadMap(mtile);
    createTilesClip();
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    damage = 0;
}

commom::~commom(){
    if(mTexture[MAP_TEXTURE] == NULL){
        SDL_DestroyTexture(mTexture[MAP_TEXTURE]);
    }
    mTexture[MAP_TEXTURE] = NULL;
}

bool commom::checkCollision(SDL_Rect a, SDL_Rect b){
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
bool commom::checkInit(){
    if(!mWindow.init()){
        std::cout << "unable create window in game.h\n";
        return false;
    }
    return true;
}

bool commom::checkLoadFile(){

    mTexture[BACKGROUND_TEXTURE] = mWindow.loadFromFile("image//background.png");
    if(mTexture[BACKGROUND_TEXTURE] == NULL){
        std::cout << "unable load background image\n";
        return false;
    }
    mTexture[MAP_TEXTURE] = mWindow.loadFromFile("image//tile.png");
    if(mTexture[MAP_TEXTURE] == NULL){
        std::cout << "unable load image\n";
        return false;
    }
    mTexture[PLAYER_TEXTURE] = mWindow.loadFromFile("image//player.png");

    if(mTexture[PLAYER_TEXTURE] == NULL){
        std::cout << "unable load player_texture\n";
        return false;
    }
    mTexture[MONSTER_TEXTURE] = mWindow.loadFromFile("image//monster.png");
    if(mTexture[MONSTER_TEXTURE] == NULL){
        std::cout << "unable load monster texture\n";
        return false;
    }
    mTexture[WIZARD_TEXTURE] = mWindow.loadFromFile("image//wizard.png");
    if(mTexture[WIZARD_TEXTURE] == NULL){
        std::cout << "unable load wizard texture\n";
        return false;
    }
    mTexture[HEALTH_TEXTURE] = mWindow.loadFromFile("image//health.png");
    if(mTexture[HEALTH_TEXTURE] == NULL){
        std::cout << "unable load health texture\n";
        return false;
    }
    mTexture[HP_ENEMY_TEXTURE] = mWindow.loadFromFile("image//hpenemy.png");
    if(mTexture[HP_ENEMY_TEXTURE] == NULL){
        std::cout << "unable load hp enemy texture\n";
        return false;
    }
    mTexture[MENU_TEXTURE] = mWindow.loadFromFile("image//menu.png");
    if(mTexture[MENU_TEXTURE] == NULL){
        std::cout << "unable load menu texture\n";
        return false;
    }
    mTexture[BOSS_TEXTURE] = mWindow.loadFromFile("image//boss.png");
    if(mTexture[BOSS_TEXTURE] == NULL){
        std::cout << "unable load boss texture\n";
        return false;
    }
    mTexture[BOSS_HP_TEXTURE] = mWindow.loadFromFile("image//bosshp.png");
    if(mTexture[BOSS_HP_TEXTURE] == NULL){
        std::cout << "unable load boss hp texture\n";
        return false;
    }
    mTexture[SKILL_TEXTURE] = mWindow.loadFromFile("image//skill.png");
    if(mTexture[SKILL_TEXTURE] == NULL){
        std::cout << "unable load boss hp texture\n";
        return false;
    }

    return true;
}
void commom::createTilesClip(){
    int x = 0; int y = 0;
    for(int i = 0; i < TILES_CLIP; i++){
        mTilesClip[i] = {x, y, 48, 48};
        x += 48;
        if(x >= 480){
            x = 0;
            y += 48;
        }
    }
}

void commom::setEnemy(){
    mMonster.clear();
    mWizard.clear();
    mMonster.push_back(monster(2016, 1269));
    mMonster.push_back(monster(2160, 1269));
    mMonster.push_back(monster(2832, 1269));
    mMonster.push_back(monster(3792, 1221));
    mMonster.push_back(monster(4320, 1221));
    mMonster.push_back(monster(5184, 1509));
    mMonster.push_back(monster(5760, 1509));
    mMonster.push_back(monster(6144, 1221));
    mMonster.push_back(monster(6624, 1221));
    mMonster.push_back(monster(6960, 1221));
    mMonster.push_back(monster(6672, 693));
    mMonster.push_back(monster(7632, 981));
    mMonster.push_back(monster(8112, 981));
    mMonster.push_back(monster(8352, 1365));
    mMonster.push_back(monster(8256, 1605));
    mMonster.push_back(monster(8880, 1269));
    mMonster.push_back(monster(9504, 1269));
    mMonster.push_back(monster(9696, 1269));
    mMonster.push_back(monster(10416, 1793));
    mMonster.push_back(monster(10944, 1653));
    mMonster.push_back(monster(11136, 981));
    mMonster.push_back(monster(12672, 1413));
    mMonster.push_back(monster(11856, 693));
    mMonster.push_back(monster(12768, 1701));
    mMonster.push_back(monster(13728, 837));
    mMonster.push_back(monster(13488, 1605));
    mMonster.push_back(monster(13632, 1605));
    mMonster.push_back(monster(13824, 1605));
    mMonster.push_back(monster(14256, 1509));
    mMonster.push_back(monster(15840, 1221));
    mMonster.push_back(monster(11760, 2037));
    mMonster.push_back(monster(12288, 2133));




    mWizard.push_back(wizard(2592, 1208));
    mWizard.push_back(wizard(3120, 1120));
    mWizard.push_back(wizard(3600, 1120));
    mWizard.push_back(wizard(4560, 1120));
    mWizard.push_back(wizard(5520, 1408));
    mWizard.push_back(wizard(5568, 928));
    mWizard.push_back(wizard(7200, 448));
    mWizard.push_back(wizard(7776, 496));
    mWizard.push_back(wizard(9072, 1120));
    mWizard.push_back(wizard(8160, 1504));
    mWizard.push_back(wizard(10128, 1264));
    mWizard.push_back(wizard(10464, 1264));
    mWizard.push_back(wizard(10848, 1312));
    mWizard.push_back(wizard(10080, 1804));
    mWizard.push_back(wizard(11040, 1984));
    mWizard.push_back(wizard(11520, 1936));
    mWizard.push_back(wizard(12384, 1312));
    mWizard.push_back(wizard(11472, 832));
    mWizard.push_back(wizard(13824, 832));
    mWizard.push_back(wizard(14976, 1648));
    mWizard.push_back(wizard(15216, 1648));
    mWizard.push_back(wizard(16086, 1168));
    mPlayer = player();
    mBoss = boss();
}
void commom::handlePlayer(SDL_Event &e){
    mMenu.handle(e, gameState);
        if(gameState == PLAY_STATE){
            is_play = true;
            is_menu = false;
            setEnemy();
            gameState = -1;
        }
    if(is_play){

        mPlayer.handle(e);
    }
    if(mPlayer.getIsDeath())
        mReload.handle(e);
}

void commom::setCamera(){
    SDL_Rect cam = mPlayer.getBox();
    camera.x = (cam.x + PLAYER_WIDTH/2) - SCREEN_WIDTH/2;
    camera.y = (cam.y + PLAYER_HEIGHT/2) - SCREEN_HEIGHT*2/3;
    if(camera.x < 0){
        camera.x = 0;
    }
    if(camera.y < 0){
        camera.y = 0;
    }
    if(camera.x > WIDTH_MAP - SCREEN_WIDTH){
        camera.x = WIDTH_MAP - SCREEN_WIDTH;
    }
    if(camera.y > HEIGHT_MAP - SCREEN_HEIGHT){
        camera.y = HEIGHT_MAP - SCREEN_HEIGHT;
    }

}





void commom::render(){
    mWindow.setRender();
    mWindow.renderClear();
    setCamera();
    if(is_menu)
    {
        mMenu.render(mWindow, mTexture);
    }
    if(is_play){
        mMap.renderMap(mPlayer.getVelX(), mPlayer.getFlip(), mWindow, camera, mTexture, mtile, mTilesClip);
        mPlayer.move(mtile);
        for(int i = 0; i < mMonster.size(); i++){
    //        mMonster[i].setPosX()
            mMonster[i].move(mPlayer, mtile);
            mMonster[i].render(mWindow, camera, mTexture, mPlayer);
            if(checkCollision(mPlayer.getBox(), mMonster[i].getBoxBlood())){
                mPlayer.setHP();
                mMonster[i].setBlood();
            }
            if(mMonster[i].getMonsterAttack())
                damage += 1;

        }
        for(int i = 0; i < mWizard.size(); i++){
            mWizard[i].setPosX();
            mWizard[i].move(mPlayer, mtile);
            mWizard[i].render(mWindow, camera, mTexture, mPlayer);
            if(mWizard[i].getAttackPlayer())
                damage += 1;

        }
        mBoss.setPosX();
        mBoss.setTotal_damage();

        mBoss.move(mtile, mPlayer);
        mBoss.render(mWindow, camera, mTexture, mPlayer);
            damage += mBoss.getTotal_damage();
        mPlayer.setIsTakeHit(damage);
        mPlayer.render(mWindow, camera, mTexture);
        damage = 0;
        mWindow.renderBox(mPlayer.getBox());
        if(mPlayer.getIsDeath()){
            mReload.render(mWindow, mTexture);

            if(mReload.getRestart()){
                mPlayer = player();
                setEnemy();
                mReload = reload();
            }
        }
    }

    mWindow.renderPresent();

}

int commom::getGameState(){
    return gameState;
}

void commom::endGame(){
    mWindow.close();
}




