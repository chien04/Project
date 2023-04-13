
#include "base.h"
#include "load_image.h"
#include <iostream>

LTexture::LTexture(){
    mObject = NULL;
    Width = 0;
    Height = 0;
}

LTexture::~LTexture(){
    free();
}

void LTexture::free(){
    if(mObject != NULL){
        SDL_DestroyTexture(mObject);
    }
    Width = 0;
    Height = 0;
}

bool LTexture::loadFromFile(std::string path){
//    bool success = true;
//    free();
//
//    SDL_Texture* newObject = NULL;
//    SDL_Surface* loadSurface = IMG_Load(path.c_str());
//    if(loadSurface == NULL){
//        std::cout << "loadSurface is erorr\n";
//    }
//    else{
//        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 255, 255, 255));
//
//        newObject = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
//        if(newObject == NULL){
//            std::cout << "newObject is error\n";
//        }
//        else{
//            Width = loadSurface->w;
//            Height = loadSurface->h;
//        }
//        SDL_FreeSurface(loadSurface);
//    }
    free();

    //The final texture
    SDL_Texture* newObject = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newObject = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newObject == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            Width = loadedSurface->w;
            Height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    mObject = newObject;

    return mObject != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(mObject, red, green, blue);
}

void LTexture::setBlendMod(SDL_BlendMode blenDing){
    SDL_SetTextureBlendMode(mObject, blenDing);
}

void LTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(mObject, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderquad = {x, y, Width, Height};
    if(clip != NULL){
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mObject, clip, &renderquad, angle, center, flip);
}

//void LTexture::push(){
//    background.render(x, y);
//}
SDL_Texture* LTexture::getObject(){
    return mObject;
}

int LTexture::getWidth(){
    return Width;
}
int LTexture::getHeight(){
    return Height;
}

