#include "Player.h"
#include "game.h"

Player::Player() {}
Player::~Player() {}

void Player::initPlayer(const char * textureSheet) {
	texPlayer = new TextureManager(textureSheet);
	texPlayer->srcRect = {0, 0, 80, 80};
}


void Player::Play(int colorType){
    keyState = SDL_GetKeyboardState(NULL);
	if(keyState[SDL_SCANCODE_RIGHT]){
		texPlayer->srcRect.y = 2 * 80;
		if(Map::canRight(texPlayer->dstRect, 5)){
			texPlayer->dstRect.x += 5;
		}
	}
	if(keyState[SDL_SCANCODE_LEFT]){
		texPlayer->srcRect.y = 1 * 80;
		if(Map::canLeft(texPlayer->dstRect, 5)){
			texPlayer->dstRect.x -= 5;
		}
	}
	if(keyState[SDL_SCANCODE_UP]){
		texPlayer->srcRect.y = 3 * 80;
		if(Map::canUp(texPlayer->dstRect, 5)){
			texPlayer->dstRect.y -= 5;
		}
	}	
	if(keyState[SDL_SCANCODE_DOWN]){
		texPlayer->srcRect.y = 0 * 80; 
		if(Map::canDown(texPlayer->dstRect, 5)){
			texPlayer->dstRect.y += 5;
		}
	}

	Game::frameTime += Game::deltaTime;
	if(Game::frameTime >= 0.1){
		Game::frameTime = 0;
		texPlayer->srcRect.x += 80;
		if(texPlayer->srcRect.x >= colorType * 240){
    		texPlayer->srcRect.x = (colorType - 1) * 240;
		} 
	}
}

void Player::Render(){
	texPlayer->Draw();
}

void Player::Clean(){
	texPlayer->~TextureManager();
}

bool Player::CollideToGhost(Ghost * ghost){
	if(texPlayer->collideTo(ghost->texGhost)) {
		playerDie += 1;
		return true;
	}
	return false;
}