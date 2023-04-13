#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include "base.h"
#include <string>
class LTexture{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);

    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMod(SDL_BlendMode blenDing);
    void setAlpha(Uint8 alpha);
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);
//    void push();

    int getWidth();
    int getHeight();
    SDL_Texture* getObject();

private:
    SDL_Texture* mObject;
    int Width;
    int Height;
};

#endif // LOAD_IMAGE_H
