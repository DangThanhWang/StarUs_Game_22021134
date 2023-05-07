#include "Bomb.h"
#include "game.h"

Bomb::Bomb() {}
Bomb::~Bomb() {}

void Bomb::init() {
    for(int i = 0; i < 10; i++){
        bomb[i] = new TextureManager("data/explode3.png");
        bomb[i]->srcRect = {0, 0, 100, 100};
        bomb[i]->dstRect = {-40, -40, 0, 0};
    }
    soundBomb = Mix_LoadWAV("data/bomb3.wav");
}

bool Bomb::collideTo(Player * player){
    for(int i = 0; i < 10; i++){
        if(bomb[i]->collideTo(player->texPlayer)) {
            return true;
        }
    }
    return false;
}

void Bomb::play(){
    timeBomb += Game::deltaTime;
    if(timeBomb >= 2.5) {
        if(timeBomb - 2.5 < 0.1) Mix_PlayChannel(-1, soundBomb, 0); 
        explode = true;
        bomb[modeBomb]->srcRect.x += 100;
        if(bomb[modeBomb]->srcRect.x >= 900){
            bomb[modeBomb]->srcRect.x = 0;
            bomb[modeBomb]->srcRect.y += 100;
            if(bomb[modeBomb]->srcRect.y >= 600){
                timeBomb = 0;
                bomb[modeBomb]->srcRect.y = 0;
                bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
                srand(time(NULL));
                modeBomb = rand() % 10;
                explode = false;
            }
        }
    }
    if(modeBomb == 0) {
        if(explode) bomb[modeBomb]->dstRect = {200, 40, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 1) {
        if(explode) bomb[modeBomb]->dstRect = {600, 40, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 2) {
        if(explode) bomb[modeBomb]->dstRect = {0, 280, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 3) {
        if(explode) bomb[modeBomb]->dstRect = {200, 280, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 4) {
        if(explode) bomb[modeBomb]->dstRect = {440, 360, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 5) {
        if(explode) bomb[modeBomb]->dstRect = {280, 480, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 6) {
        if(explode) bomb[modeBomb]->dstRect = {640, 480, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 7) {
        if(explode) bomb[modeBomb]->dstRect = {200, 680, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 8) {
        if(explode) bomb[modeBomb]->dstRect = {560, 720, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
    if(modeBomb == 9) {
        if(explode) bomb[modeBomb]->dstRect = {760, 280, 40, 40};
        else bomb[modeBomb]->dstRect = {-40, -40, 0, 0};
    }
}

void Bomb::Render(){
    bomb[modeBomb]->Draw();
}