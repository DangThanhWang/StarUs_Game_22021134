#pragma once
#include <SDL2/SDL.h>
#include <ctime>
#include "MapManager.h"
#include <map>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

enum {
    GO_NONE,
    GO_UP,
    GO_DOWN,
    GO_LEFT,
    GO_RIGHT
};

class Ghost {
public:
    Ghost();
    ~Ghost();
    TextureManager * texGhost;
    void initGhost(const char * path);
    void returnNewMoveSpeed(float newMoveSpeed);
    void AutoAIdirection(SDL_Rect playerPosition, int numGhost);
    void AutoDirection(SDL_Rect playerPosition, int numGhost);
    void SetDirection();
    void Play();
    void Render();
    void Clean();
    
    int directionCurrent;
    int directionAuto;
private:
    float distance = 999999;
    int minDirect;
    float minDistance = 99999;
    int moveSpeed;
    int NumGhost;
    float frameTimeGhost = 0;
    int xposGhost, yposGhost;
};