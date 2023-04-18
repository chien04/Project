#ifndef BASE_H_
#define BASE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "hangso_const.h"


class createWindow{
public:
    createWindow();
    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    SDL_Texture* loadFromFile(std::string path);
    void render(SDL_Texture* object, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, double width_real = 0, double height_real = 0);

    bool init();
    void close();

    void setRender();
    void renderClear();

    void renderPresent();
    void renderBox(SDL_Rect rect);
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
 //   SDL_Event e;
};




#endif // BASE_H_
