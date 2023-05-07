#include "game.h"

common::common(){
    for(int i = 0; i < 1005; i++){
        dd[i] = 0;
    }
    gameStateMenu = -1;
    gameStateGuide = -1;
    gameStateReload = -1;
    gameStatePause = -1;
    gameStateWin = -1;
    is_menu = true;
    is_play = false;
    is_guide = false;
    restart = false;
    cnt = 0;
    mTexture[MAP_TEXTURE] = NULL;
    mMap.loadMap(mtile);
    createTilesClip();
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    damage = 0;
    random_enemy = 0;
    tmp1 = false;
    tmp2 = false;
    score = 0;
}

common::~common(){
    if(mTexture[MAP_TEXTURE] == NULL){
        SDL_DestroyTexture(mTexture[MAP_TEXTURE]);
    }
    mTexture[MAP_TEXTURE] = NULL;
}

bool common::checkCollision(SDL_Rect a, SDL_Rect b){
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
bool common::checkInit(){
    if(!mWindow.init()){
        std::cout << "unable create window in game.h\n";
        return false;
    }
    return true;
}

bool common::checkLoadFile(){

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
    mTexture[GUIDE_TEXTURE] = mWindow.loadFromFile("image//guide.png");
    if(mTexture[GUIDE_TEXTURE] == NULL){
        std::cout << "unable load guide texture\n";
        return false;
    }
    mTexture[EFFECT_TEXTURE] = mWindow.loadFromFile("image//effect.png");
    if(mTexture[EFFECT_TEXTURE] == NULL){
        std::cout << "unable load effect texture\n";
        return false;
    }
    mTexture[EFFECT_TEXTUREEXP] = mWindow.loadFromFile("image//effectexp.png");
    if(mTexture[EFFECT_TEXTUREEXP] == NULL){
        std::cout << "unable load effect exp texture\n";
        return false;
    }

    return true;
}

bool common::checkLoadSound(){
    gameSound[PRESS_BUTTON] = Mix_LoadWAV("sound//press_button.wav");
    if(gameSound[PRESS_BUTTON] == NULL){
        std::cout << "load sound press button is fail";
        return false;
    }
    gameSound[WIZARD_ATTACKSOUND] = Mix_LoadWAV("sound//wizard_attack.wav");
    if(gameSound[WIZARD_ATTACKSOUND] == NULL){
        std::cout << "load sound wizard attack sound is fail";
        return false;
    }
    gameSound[WIZARD_TAKEHITSOUND] = Mix_LoadWAV("sound//takehit.wav");
    if(gameSound[WIZARD_TAKEHITSOUND] == NULL){
        std::cout << "load sound wizard takehit sound is fail";
        return false;
    }
    gameSound[WIZARD_DEATHSOUND] = Mix_LoadWAV("sound//wizard_death.wav");
    if(gameSound[WIZARD_DEATHSOUND] == NULL){
        std::cout << "load sound wizard death sound is fail";
        return false;
    }
    gameSound[PLAYER_ATTACKSOUND] = Mix_LoadWAV("sound//playerattack.wav");
    if(gameSound[PLAYER_ATTACKSOUND] == NULL){
        std::cout << "load sound playear attack sound is fail";
        return false;
    }
    gameSound[PLAYER_RUNSOUND] = Mix_LoadWAV("sound//playerrun.wav");
    if(gameSound[PLAYER_RUNSOUND] == NULL){
        std::cout << "load sound player run sound is fail";
        return false;
    }
    gameSound[PLAYER_ATTACKMISSSOUND] = Mix_LoadWAV("sound//playerattackmiss.wav");
    if(gameSound[PLAYER_ATTACKMISSSOUND] == NULL){
        std::cout << "load sound player attack miss sound is fail";
        return false;
    }
    gameSound[PLAYER_JUMPSOUND] = Mix_LoadWAV("sound//playerjump.wav");
    if(gameSound[PLAYER_JUMPSOUND] == NULL){
        std::cout << "load sound player jump sound is fail";
        return false;
    }
    gameSound[PLAYER_DAMAGESOUND] = Mix_LoadWAV("sound//playerdamage.wav");
    if(gameSound[PLAYER_DAMAGESOUND] == NULL){
        std::cout << "load sound player damage sound is fail";
        return false;
    }
    gameSound[PLAYER_DEATHSOUND] = Mix_LoadWAV("sound//playerdeath.wav");
    if(gameSound[PLAYER_DEATHSOUND] == NULL){
        std::cout << "load sound player death sound is fail";
        return false;
    }
    gameSound[PLAYER_ATTACKSKILLSOUND] = Mix_LoadWAV("sound//playerattackskill.wav");
    if(gameSound[PLAYER_ATTACKSKILLSOUND] == NULL){
        std::cout << "load sound player attack skill sound is fail";
        return false;
    }
    gameSound[MONSTER_ATTACKSOUND] = Mix_LoadWAV("sound//monsterattack.wav");
    if(gameSound[MONSTER_ATTACKSOUND] == NULL){
        std::cout << "load sound monster attack sound is fail";
        return false;
    }
    gameSound[MONSTER_TAKEHITSOUND] = Mix_LoadWAV("sound//monstertakehit.wav");
    if(gameSound[MONSTER_TAKEHITSOUND] == NULL){
        std::cout << "load sound player attack skill sound is fail";
        return false;
    }
    gameSound[MONSTER_DEATHSOUND] = Mix_LoadWAV("sound//monsterdeath.wav");
    if(gameSound[MONSTER_DEATHSOUND] == NULL){
        std::cout << "load sound player attack skill sound is fail";
        return false;
    }
    gameSound[BOSS_LIGHTNINGSOUND] = Mix_LoadWAV("sound//lightning.wav");
    if(gameSound[BOSS_LIGHTNINGSOUND] == NULL){
        std::cout << "load sound boss lightning sound is fail";
        return false;
    }
    gameSound[BOSS_FIRESOUND] = Mix_LoadWAV("sound//bossattackfire.wav");
    if(gameSound[BOSS_FIRESOUND] == NULL){
        std::cout << "load sound boss attack fire sound is fail";
        return false;
    }
    gameSound[BOSS_DEATHSOUND] = Mix_LoadWAV("sound//bossdeath.wav");
    if(gameSound[BOSS_DEATHSOUND] == NULL){
        std::cout << "load sound boss death sound is fail";
        return false;
    }
    gameSound[PLAYER_HEALINGSOUND] = Mix_LoadWAV("sound//playerhealing.wav");
    if(gameSound[PLAYER_HEALINGSOUND] == NULL){
        std::cout << "load sound player healing sound is fail";
        return false;
    }
    gameSound[USE_ITEMSOUND] = Mix_LoadWAV("sound//useitem.wav");
    if(gameSound[USE_ITEMSOUND] == NULL){
        std::cout << "load sound player healing sound is fail";
        return false;
    }
        gameSound[USE_ITEMSOUND] = Mix_LoadWAV("sound//useitem.wav");
    if(gameSound[USE_ITEMSOUND] == NULL){
        std::cout << "load sound item healing sound is fail";
        return false;
    }
    gameSound[ATTACK_CHESTSOUND] = Mix_LoadWAV("sound//attackchest.wav");
    if(gameSound[ATTACK_CHESTSOUND] == NULL){
        std::cout << "load sound player attack chest sound is fail";
        return false;
    }

    gameMusic[MUSIC_HOME] = Mix_LoadMUS("music//musichome.wav");
    if(gameMusic[MUSIC_HOME] == NULL){
        std::cout << "load music home is fail";
        return false;
    }
    gameMusic[MUSIC_BATTLE] = Mix_LoadMUS("music//musicbattle.wav");
    if(gameMusic[MUSIC_BATTLE] == NULL){
        std::cout << "load music home is fail";
        return false;
    }
    return true;
}
void common::createTilesClip(){
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

void common::setEnemy(){
    mMonster.clear();
    mWizard.clear();
    mMonster.push_back(monster(2016, 1269, 0));
    mMonster.push_back(monster(2160, 1269, 0));
    mMonster.push_back(monster(2832, 1269, 0));
    mMonster.push_back(monster(3792, 1221, 0));
    mMonster.push_back(monster(4320, 1221, 0));
    mMonster.push_back(monster(5184, 1509, 1));
    mMonster.push_back(monster(5760, 1509, 0));
    mMonster.push_back(monster(6144, 1221, 0));
    mMonster.push_back(monster(6624, 1221, 0));
    mMonster.push_back(monster(6960, 1221, 1));
    mMonster.push_back(monster(6672, 693, 0));
    mMonster.push_back(monster(7632, 981, 0));
    mMonster.push_back(monster(8112, 981, 0));
    mMonster.push_back(monster(8352, 1365, 0));
    mMonster.push_back(monster(8256, 1605, 1));
    mMonster.push_back(monster(8880, 1269, 0));
    mMonster.push_back(monster(9504, 1269, 0));
    mMonster.push_back(monster(9696, 1269, 1));
    mMonster.push_back(monster(10416, 1793, 0));
    mMonster.push_back(monster(10944, 1653, 0));
    mMonster.push_back(monster(11136, 981, 1));
    mMonster.push_back(monster(12672, 1413, 0));
    mMonster.push_back(monster(11856, 693, 0));
    mMonster.push_back(monster(12768, 1701, 0));
    mMonster.push_back(monster(13728, 837, 1));
    mMonster.push_back(monster(13488, 1605, 0));
    mMonster.push_back(monster(13632, 1605, 0));
    mMonster.push_back(monster(13824, 1605, 0));
    mMonster.push_back(monster(14256, 1509, 0));
    mMonster.push_back(monster(15840, 1221, 1));
    mMonster.push_back(monster(11760, 2037, 0));
    mMonster.push_back(monster(12288, 2133, 1));




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
void common::handlePlayer(SDL_Event &e){
    if(is_menu){
        score = 0;
        if(tmp1 == false)
            Mix_PlayMusic(gameMusic[MUSIC_HOME], -1);
        tmp1 = true;
        mMenu.handle(e, gameStateMenu, gameSound);
            if(gameStateMenu == PLAY_STATE){
                Mix_HaltMusic();
                is_play = true;
                tmp2 = false;
                is_menu = false;
                setEnemy();
                gameStateMenu = -1;
            }
            if(gameStateMenu == GUIDE_STATE){
                is_guide = true;
                is_menu = false;
                gameStateMenu = -1;
            }
    }
    if(is_guide){
        mGuide.handle(e, gameStateGuide, gameSound);
        if(gameStateGuide == MENU_STATE){
            is_menu = true;
            is_guide = false;
            gameStateGuide = -1;
        }
    }
    if(is_play){
        if(tmp2 == false)
            Mix_PlayMusic(gameMusic[MUSIC_BATTLE], -1);
        tmp2 = true;
        mPlayer.handle(e, gameSound);
    }
    if(mPlayer.getPause()){
        mPause.handle(e, gameStatePause, gameSound);
        if(gameStatePause == CONTINUTE_STATE){
            mPlayer.setPause();
            gameStatePause = -1;
        }
        if(gameStatePause == RELOAD_STATEPAUSE){
            restart = true;
            gameStatePause = -1;
            mPlayer.setPause();
        }
        if(gameStatePause == MENU_STATEPAUSE){
            Mix_HaltMusic();
            is_menu = true;
            tmp1 = false;
            is_play = false;
            restart = false;
            gameStatePause = -1;
            mPlayer.setPause();
        }
    }
    if(mPlayer.getIsDeath()){
        mReload.handle(e, gameStateReload, gameSound);
        if(gameStateReload == RELOAD_STATE){
            restart = true;
            gameStateReload = -1;
        }
        if(gameStateReload == MENU_STATE){
            is_menu = true;
            is_play = false;
            restart = false;
            gameStateReload = -1;
        }
    }
    if(mBoss.getDeath()){
        mWon.handle(e, gameStateWin, gameSound);
        if(gameStateWin == RELOAD_STATE){
            restart = true;
            gameStateWin = -1;
        }
        if(gameStateWin == MENU_STATE){
            is_menu = true;
            is_play = false;
            restart = false;
            gameStateWin = -1;
        }
    }
}

void common::setCamera(){
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

bool common::checkLoadFont(){
    mFont = TTF_OpenFont("font//PressStart2P-Regular.ttf", 24);
    if(mFont == NULL){
        std::cout << "font is fail";
        return false;
    }
    fontArial = TTF_OpenFont("font//Arialn.ttf", 70);
    if(fontArial == NULL){
        std::cout << "font is fail";
        return false;
    }
    return true;
}
void common::renderScore(){
    SDL_Color textColor = {0, 255, 255, 0};
    SDL_Color textColor1 = {0, 0, 0, 255};
    scoreText.str("");
    scoreText << "Score: " << score;
    iTemHp.str("");
    iTemHp << mPlayer.getHealingFull();
    iTemExp.str("");
    iTemExp << mPlayer.getExpFull();
    mWindow.LoadFromRenderText(mFont, scoreText.str().c_str(), textColor, 300, 50);
    mWindow.LoadFromRenderText(mFont, "HightScore 4000", textColor, 300, 10);
    mWindow.LoadFromRenderText(mFont, iTemHp.str().c_str(), textColor, 75, 155);
    mWindow.LoadFromRenderText(mFont, iTemExp.str().c_str(), textColor, 195, 155);
    if(mBoss.getDeath())
        mWindow.LoadFromRenderText(fontArial, scoreText.str().c_str(), textColor1, 500, 300);
    if(mPlayer.getIsDeath())
        mWindow.LoadFromRenderText(fontArial, scoreText.str().c_str(), textColor1, 500, 250);
}



void common::render(){
    mWindow.setRender();
    mWindow.renderClear();
    setCamera();
    if(is_menu)
    {
        mMenu.render(mWindow, mTexture);
    }
    if(is_guide)
        mGuide.render(mWindow, mTexture);
    if(is_play){
        if(mBoss.getCnt()){
            random_enemy = rand() % 2;
                if(random_enemy == 0)
                    mMonster.push_back(monster(mBoss.getPosX(), 0, 1));
                if(random_enemy == 1)
                    mWizard.push_back(wizard(mBoss.getPosX() , 0));
            mBoss.setCnt();
        }

        mMap.renderMap(mPlayer.getVelX(), mPlayer.getFlip(), mWindow, camera, mTexture, mtile, mTilesClip);
        mPlayer.move(mtile, gameSound);
        if(!mBoss.getDeath()){
        for(int i = 0; i < mMonster.size(); i++){
    //        mMonster[i].setPosX()
            mMonster[i].move(mPlayer, mtile);
            mMonster[i].render(mWindow, camera, mTexture, mPlayer, gameSound);
            if(checkCollision(mPlayer.getBox(), mMonster[i].getBoxBlood())){
                Mix_PlayChannel(-1, gameSound[PLAYER_HEALINGSOUND], 0);
                mPlayer.setHP();
                mMonster[i].setBlood();
                mMonster.erase(mMonster.begin() + i);

            }
            if(mMonster[i].getDeath() && dd[i] == 0){
                score += 15;
                dd[i] = 1;
            }
            if(mMonster[i].getMonsterAttack())
                damage += 1;
            if(mMonster[i].getIsTakeHit()){
                cnt++;
            }
        }
        for(int i = 0; i < mWizard.size(); i++){
            mWizard[i].setPosX();
            mWizard[i].move(mPlayer, mtile);
            mWizard[i].render(mWindow, camera, mTexture, mPlayer, gameSound);
            if(mWizard[i].getAttackPlayer())
                damage += 1;
            if(mWizard[i].getIsTakeHit())
                cnt++;
            if(mWizard[i].getDeath()){
                mWizard.erase(mWizard.begin() + i);
                score += 10;
            }
        }
        }
        mBoss.setPosX();
        mBoss.setTotal_damage();
        mBoss.move(mtile, mPlayer);
        mBoss.render(mWindow, camera, mTexture, mPlayer, gameSound);
        damage += mBoss.getTotal_damage();

        if(mBoss.getIsTakeHit())
            cnt++;
        if(cnt == 3)
            mPlayer.setExp();
        if(cnt >= 3)
            cnt = 0;

        mPlayer.setIsTakeHit(damage);
        mPlayer.render(mWindow, camera, mTexture, gameSound);
        damage = 0;
//        mWindow.renderBox(mPlayer.getBox());
        if(mPlayer.getIsDeath()){
//            std::cout << 1 << std::endl;
            mReload.render(mWindow, mTexture);
        }
        if(restart){
//                    std::cout << 1;
                mPlayer = player();
                setEnemy();
                mReload = reload();
                score = 0;
                restart = false;
            }
        if(mPlayer.getPause()){
            mPause.render(mWindow, mTexture);
        }
        if(mBoss.getDeath()){
            if(dd[1000] == 0)
                score += 300;
            mWon.render(mWindow, mTexture);
            dd[1000] = 1;
        }

    }
    if(is_play){
        renderScore();
    }

    mWindow.renderPresent();

}

int common::getGameState(){
    return gameStateMenu;
}

void common::endGame(){
    for(auto texture : mTexture){
        SDL_DestroyTexture(texture);
    }
    for(auto chunk : gameSound){
        Mix_FreeChunk(chunk);
    }
    for(auto music : gameMusic){
        Mix_FreeMusic(music);
    }
    TTF_CloseFont(mFont);
    mWindow.close();
}




