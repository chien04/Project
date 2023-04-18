#include "game.h"

commom::commom(){

    mTexture[MAP_TEXTURE] = NULL;
    mMap.loadMap(mtile);
    createTilesClip();
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    mMonster[0] = monster(500, 0);
    mMonster[1] = monster(700, 0);
    mMonster[2] = monster(1000, 0);
    posX_monster[0] = mMonster[0].getPosX();
    posX_monster[1] = mMonster[1].getPosX();
    posX_monster[2] = mMonster[2].getPosX();


    mWizard[0] = wizard(500, 0);
    mWizard[1] = wizard(1400, 0);
    mWizard[2] = wizard(1800, 0);

    for(int i = 0; i < TOTAL_WIZARD; i++){
        posX_wizard[i] = mWizard[i].getPosX();
    }
    check = false;
    check_ball = false;
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
    mTexture[BACK_TEXTURE] = mWindow.loadFromFile("image//back.png");
    if(mTexture[BACK_TEXTURE] == NULL){
        std::cout << "unable load backtexture\n";
        return false;
    }
    mTexture[MIDDLE_TEXTURE] = mWindow.loadFromFile("image//middle.png");
    if(mTexture[MIDDLE_TEXTURE] == NULL){
        std::cout << "unable load backtexture\n";
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
    mTexture[EFFECT_TEXTURE] = mWindow.loadFromFile("image//effect.png");

    if(mTexture[EFFECT_TEXTURE] == NULL){
        std::cout << "unable load effect_texture\n";
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

void commom::handlePlayer(SDL_Event &e){
    mPlayer.handle(e);
    if(mPlayer.getIsDeath())
        mMenu.handle(e);
}

void commom::setCamera(){
    SDL_Rect cam = mPlayer.getBox();
    camera.x = (cam.x + PLAYER_WIDTH/2) - SCREEN_WIDTH/2;
    camera.y = (cam.y + PLAYER_HEIGHT/2) - SCREEN_HEIGHT/2;
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

    mMap.renderMap(mPlayer.getVelX(), mPlayer.getFlip(), mWindow, camera, mTexture, mtile, mTilesClip);
    mPlayer.move(mtile);
    for(int i = 0; i < TOTAL_MONSTER; i++){
        mMonster[i].move(mPlayer, mtile, posX_monster[i]);
        mMonster[i].render(mWindow, camera, mTexture, mPlayer);
        if(checkCollision(mPlayer.getBox(), mMonster[i].getBoxBlood())){
            std::cout << "not" << std::endl;
            mPlayer.setHP();
        }
        if(mMonster[i].getMonsterAttack()){
            check = true;
            break;
        }
        else
            check = false;
    }
    for(int i = 0; i < TOTAL_WIZARD; i++){
        mWizard[i].setPosX(posX_wizard[i]);
        mWizard[i].move(mPlayer, mtile, posX_wizard[i]);
        mWizard[i].render(mWindow, camera, mTexture, mPlayer);
        if(mWizard[i].getAttackPlayer()){
            check_ball = true;
            break;
        }
        else
            check_ball = false;
    }
    if(check == true || check_ball == true)
        mPlayer.setIsTakeHit(check, check_ball);
    mPlayer.render(mWindow, camera, mTexture);
    mWindow.renderBox(mPlayer.getBox());
    if(mPlayer.getIsDeath()){
        mMenu.render(mWindow, mTexture);

        if(mMenu.getRestart()){
            mPlayer = player();
            mMonster[0] = monster(500, 0);
            mMonster[1] = monster(700, 0);
            mMonster[2] = monster(1000, 0);
            posX_monster[0] = mMonster[0].getPosX();
            posX_monster[1] = mMonster[1].getPosX();
            posX_monster[2] = mMonster[2].getPosX();

            mWizard[0] = wizard(500, 0);
            mWizard[1] = wizard(1400, 0);
            mWizard[2] = wizard(1800, 0);
            mMenu = menu();
        }
    }

    mWindow.renderPresent();

}

void commom::endGame(){
    mWindow.close();
}




