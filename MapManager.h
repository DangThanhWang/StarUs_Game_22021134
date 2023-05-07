#pragma once
#include "TextureManager.h"

class Map {
public:
    static TextureManager * texMap;
    static bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
    static bool canUp(SDL_Rect rectObject, int addedValue);
    static bool canDown(SDL_Rect rectObject, int addedValue);
    static bool canLeft(SDL_Rect rectObject, int addedValue);
    static bool canRight(SDL_Rect rectObject, int addedValue);
    static void initMap();
    static SDL_Rect barriers[31];
};