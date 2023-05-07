#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextureManager {
public:
    TextureManager();
    TextureManager(const char * filename);
    ~TextureManager();

    SDL_Texture * Texture;
    SDL_Rect dstRect;
    SDL_Rect srcRect;
    
    int WidthTex, HeightTex;
    void LoadImageTex(const char * filename);
    void Draw(); 
    void Draw2();
    bool collideTo(TextureManager * TexOther);
    bool circularCollision(TextureManager * TexOther);
    bool collideToMouse();
    void LoadTexFont(const char * texString, SDL_Color color);

    static TTF_Font * font;
    static SDL_Color colorWhite;
    static SDL_Color colorPurple;
    static SDL_Color colorLavender;
    static SDL_Color colorSkyBlue;
};