#include "Ghost.h"
#include "game.h"

Ghost::Ghost() {}
Ghost::~Ghost() {}

void Ghost::initGhost(const char * path){
    texGhost = new TextureManager(path);
    texGhost->srcRect = {2640, 0, 80, 80};

    directionCurrent = GO_DOWN;
    directionAuto = GO_DOWN;
}

void Ghost::returnNewMoveSpeed(float newMoveSpeed){
    moveSpeed = newMoveSpeed;
}

void Ghost::AutoDirection(SDL_Rect playerPosition, int numGhost){
    xposGhost = texGhost->dstRect.x;
    yposGhost = texGhost->dstRect.y;
    if(xposGhost < 0 || xposGhost + 40 > 800 || yposGhost < 0 || yposGhost + 40 > 800) {
        if(numGhost == 1) {
            texGhost->dstRect.x = 80;
            texGhost->dstRect.y = 80;
        }
        if(numGhost == 2) {
            texGhost->dstRect.x = 760;
            texGhost->dstRect.y = 0;
        }
        if(numGhost == 3) {
            texGhost->dstRect.x = 0;
            texGhost->dstRect.y = 760;
        }
    }
    vector<int> candidatesDir;
	if (directionCurrent != GO_LEFT){
		if(Map::canRight(texGhost->dstRect, moveSpeed)) candidatesDir.push_back(GO_RIGHT);
	}

    if (directionCurrent != GO_RIGHT){
		if(Map::canLeft(texGhost->dstRect, moveSpeed)) candidatesDir.push_back(GO_LEFT);
	}

    if (directionCurrent != GO_DOWN){
		if(Map::canUp(texGhost->dstRect, moveSpeed)) candidatesDir.push_back(GO_UP);
	}

    if (directionCurrent != GO_UP){
		if(Map::canDown(texGhost->dstRect, moveSpeed)) candidatesDir.push_back(GO_DOWN);
	}

	if (candidatesDir.size() == 0){
		switch (directionCurrent)
		{
		case GO_UP: directionAuto = GO_DOWN; break;
		case GO_DOWN: directionAuto = GO_UP; break;
		case GO_RIGHT: directionAuto = GO_LEFT; break;
		case GO_LEFT: directionAuto = GO_RIGHT; break;
		}
	}
	else {
        srand(time(NULL));
		directionAuto = candidatesDir[rand() % candidatesDir.size()];
	}
}

void Ghost::AutoAIdirection(SDL_Rect playerPosition, int numGhost){
    xposGhost = texGhost->dstRect.x;
    yposGhost = texGhost->dstRect.y;
    if(xposGhost < 0 || xposGhost + 40 > 800 || yposGhost < 0 || yposGhost + 40 > 800) {
        if(numGhost == 1) {
            texGhost->dstRect.x = 80;
            texGhost->dstRect.y = 80;
        }
        if(numGhost == 2) {
            texGhost->dstRect.x = 760;
            texGhost->dstRect.y = 0;
        }
        if(numGhost == 3) {
            texGhost->dstRect.x = 0;
            texGhost->dstRect.y = 760;
        }
    }
    minDistance = 9999;
    minDirect = 0;
    if(directionCurrent != GO_UP && Map::canDown(texGhost->dstRect, moveSpeed)){
        distance = sqrt( (playerPosition.x - texGhost->dstRect.x) * (playerPosition.x - texGhost->dstRect.x) + (playerPosition.y - texGhost->dstRect.y - moveSpeed) * (playerPosition.y - texGhost->dstRect.y - moveSpeed) );
        if(distance < minDistance){
            minDistance = distance;
            minDirect = GO_DOWN;
        }
    }
    if(directionCurrent != GO_DOWN && Map::canUp(texGhost->dstRect, moveSpeed)){
        distance = sqrt( (playerPosition.x - texGhost->dstRect.x) * (playerPosition.x - texGhost->dstRect.x) + (playerPosition.y - texGhost->dstRect.y + moveSpeed) * (playerPosition.y - texGhost->dstRect.y + moveSpeed) );
        if(distance < minDistance){
            minDistance = distance;
            minDirect = GO_UP;
        }
    }
    if(directionCurrent != GO_LEFT && Map::canRight(texGhost->dstRect, moveSpeed)){
        distance = sqrt( (playerPosition.x - texGhost->dstRect.x - moveSpeed) * (playerPosition.x - texGhost->dstRect.x - moveSpeed) + (playerPosition.y - texGhost->dstRect.y) * (playerPosition.y - texGhost->dstRect.y) );
        if(distance < minDistance){
            minDistance = distance;
            minDirect = GO_RIGHT;
        }
    }
    if(directionCurrent != GO_RIGHT && Map::canLeft(texGhost->dstRect, moveSpeed)){
        distance = sqrt( (playerPosition.x - texGhost->dstRect.x + moveSpeed) * (playerPosition.x - texGhost->dstRect.x + moveSpeed) + (playerPosition.y - texGhost->dstRect.y) * (playerPosition.y - texGhost->dstRect.y) );
        if(distance < minDistance){
            minDistance = distance;
            minDirect = GO_LEFT;
        }
    } 
    if(minDistance == 9999) {
        switch (directionCurrent)
        {
        case GO_UP: 
            directionAuto = GO_DOWN;
            break;
        case GO_DOWN:
            directionAuto = GO_UP;
            break;
        case GO_LEFT:
            directionAuto = GO_RIGHT;
            break;
        case GO_RIGHT:
            directionAuto = GO_LEFT;
            break;
        }
    } else {
        directionAuto = minDirect;
    }
}

void Ghost::SetDirection(){
    if (directionCurrent!= GO_DOWN && directionAuto == GO_DOWN && Map::canDown(texGhost->dstRect, moveSpeed)){
		directionCurrent = GO_DOWN;
        return;
	}
    if (directionCurrent!= GO_UP && directionAuto == GO_UP && Map::canUp(texGhost->dstRect, moveSpeed)){
		directionCurrent = GO_UP;
        return;
	}
    if (directionCurrent!= GO_LEFT && directionAuto == GO_LEFT && Map::canLeft(texGhost->dstRect, moveSpeed)){
		directionCurrent = GO_LEFT;
        return;
	}
    if (directionCurrent!= GO_RIGHT && directionAuto == GO_RIGHT && Map::canRight(texGhost->dstRect, moveSpeed)){
		directionCurrent = GO_RIGHT;
        return;
	}
}

void Ghost::Play(){
    if(directionCurrent == GO_UP && Map::canUp(texGhost->dstRect, moveSpeed)){
        texGhost->srcRect.y = 3 * texGhost->srcRect.h;
        texGhost->dstRect.y -= moveSpeed;
    }
    else if(directionCurrent == GO_DOWN && Map::canDown(texGhost->dstRect, moveSpeed)){
        texGhost->srcRect.y = 0;
        texGhost->dstRect.y += moveSpeed;
    }
    else if(directionCurrent == GO_LEFT && Map::canLeft(texGhost->dstRect, moveSpeed)){
        texGhost->srcRect.y = 1 * texGhost->srcRect.h;
        texGhost->dstRect.x -= moveSpeed;
    }
    else if(directionCurrent == GO_RIGHT && Map::canRight(texGhost->dstRect, moveSpeed)){
        texGhost->srcRect.y = 2 * texGhost->srcRect.h;
        texGhost->dstRect.x += moveSpeed;
    }

    frameTimeGhost += Game::deltaTime;
    if(frameTimeGhost >= 0.1) {
        frameTimeGhost = 0;
        texGhost->srcRect.x += 80;
        if(texGhost->srcRect.x >= 2880) {
            texGhost->srcRect.x = 2640;
        }
    }
}

void Ghost::Render(){
    texGhost->Draw();
}

void Ghost::Clean(){
    texGhost->~TextureManager();
}