#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "Ghost.h"

class Player {
public:
    Player();
    ~Player();
    void initPlayer(const char * textureSheet);
    void Play(int colorType);
    void Render();
    void Clean();
    bool CollideToGhost(Ghost * ghost);

	const Uint8 * keyState;
    int frameWidth, frameHeight;

    TextureManager * texPlayer;
    
    int playerDie = 0;
};