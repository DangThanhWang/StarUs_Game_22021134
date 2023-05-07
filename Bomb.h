#pragma once

#include "TextureManager.h"
#include "Player.h"

class Bomb {
public:
    Bomb();
    ~Bomb();
    void init();
    bool collideTo(Player * player);
    void play();
    void Render();
private:
    TextureManager * bomb[10];
    float timeBomb = 0;
    int modeBomb = 0;
    bool explode = false;
    Mix_Chunk * soundBomb;
};
