#pragma once

#include "TextureManager.h"
#include "Player.h"
#include <fstream>

class Coin {
public:
    Coin();
    ~Coin();
    TextureManager * texCoin[20][20];
    void init(const char * filename);
    void returnPosition();
    void coinRender();
    void takeScore(Player * player);

    int Score = 0;
    int score();
private:
    int arr[20][20];
    int numCoin = 1;
    float frameTimeCoin = 0;
};