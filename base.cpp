#include "base.h"
#include "game.h"
createWindow background;
createWindow::createWindow(){
    gWindow = NULL;
    gRenderer = NULL;

}

//void createWindow::setColor(Uint8 red, Uint8 green, Uint8 blue){
//    SDL_SetTextureColorMod(, red, green, blue);
//}
SDL_Texture* createWindow::loadFromFile(std::string path){
//    std::cout << (gRenderer != NULL) << '\n';
    SDL_Texture* newObject = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if(loadSurface == NULL){
        std::cout << "loadSurface is erorr\n";
    }
    else{
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 255, 255, 255));

        newObject = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if(newObject == NULL){
            std::cout << "newObject is error: " << SDL_GetError() << path << '\n';
        }
        SDL_FreeSurface(loadSurface);
    }
    return newObject;
}

void createWindow::render(SDL_Texture* object, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center,
                           SDL_RendererFlip flip, double width_real, double height_real){
    SDL_Rect renderquad = {x, y, width_real, height_real};
//    if(clip != NULL){
//        renderquad.w = clip->w;
//        renderquad.h = clip->h;
//    }
    SDL_RenderCopyEx(gRenderer, object, clip, &renderquad, angle, center, flip);
}

bool createWindow::init(){
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }
    }
//    std::cout << (gRenderer != NULL) << '\n';
    return success;
}

void createWindow::close(){


    SDL_DestroyWindow(gWindow);

    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);

    gRenderer = NULL;

}

void createWindow::setRender(){
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
}

void createWindow::renderClear(){
    SDL_RenderClear(gRenderer);
}

void createWindow::renderPresent(){
    SDL_RenderPresent(gRenderer);
}

void createWindow::renderBox(SDL_Rect rect){
    SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 100);
    SDL_RenderDrawRect(gRenderer, &rect);
}
