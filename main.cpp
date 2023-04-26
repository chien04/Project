#include "game.h"
#include "player.h"
using namespace std;

commom fix;

int main(int argc, char* args[])
{
    if(!fix.checkInit()){
        std::cout << "init is error\n";
    }
    else{
        if(!fix.checkLoadFile()){
            std::cout << "load file is error\n";
        }
        else{
            bool quit = false;
            SDL_Event e;
            while(!quit){
                while(SDL_PollEvent( &e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;

                    }
                    fix.handlePlayer(e);
                    if(fix.getGameState() == QUIT_STATE)
                        quit = true;

                }
                fix.render();
            }
        }
    }
    fix.endGame();
    return 0;
}

