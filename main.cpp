#include "game.h"
#include "time.h"
using namespace std;

common mGame;

LTimer mTime;
int main(int argc, char* args[])
{
    if(!mGame.checkInit()){
        std::cout << "init is error\n";
    }
    else{
        if(!mGame.checkLoadFile()){
            std::cout << "load file is error\n";
        }
        if(!mGame.checkLoadSound())
            std::cout << "load sound is error\n";
        if(!mGame.checkLoadFont()){
            std::cout << "load font is error";
        }
        else{
            bool quit = false;
            SDL_Event e;
            while(!quit){
                mTime.start();
                while(SDL_PollEvent( &e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;

                    }
                    mGame.handlePlayer(e);
                    if(mGame.getGameState() == QUIT_STATE)
                        quit = true;

                }
                mGame.render();
                int frameTicks = mTime.getTicks();
                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                {
                    //Wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                }
            }
        }
    }
    mGame.endGame();
    return 0;
}

