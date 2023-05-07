#include "Coin.h"
#include "game.h"

Coin::Coin() {}
Coin::~Coin() {}

int Coin::score(){
    return Score;
}

void Coin::init(const char * filename){
    ifstream infile("filecoin.txt");
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++){
            infile >> arr[i][j];
            texCoin[i][j] = new TextureManager(filename);
            if(arr[i][j] == 1) {
                numCoin++;
                texCoin[i][j]->srcRect = {0, 0, texCoin[i][j]->WidthTex / 10, texCoin[i][j]->HeightTex};
                texCoin[i][j]->dstRect = {j * 40, i * 40, 40, 40};
            } else {
                texCoin[i][j]->dstRect = {-40, -40, -40, -40};
            }
        } 
    }
}

void Coin::returnPosition(){
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++){
            if(arr[i][j] == 1) {
                texCoin[i][j]->srcRect = {0, 0, texCoin[i][j]->WidthTex / 10, texCoin[i][j]->HeightTex};
                texCoin[i][j]->dstRect = {j * 40, i * 40, 40, 40};
            } else {
                texCoin[i][j]->dstRect = {-40, -40, -40, -40};
            }
        }
    }
}

void Coin::coinRender(){
    frameTimeCoin += Game::deltaTime;
    if(frameTimeCoin >= 0.1) {
        frameTimeCoin = 0;
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 20; j++){
                if(arr[i][j] == 1) {
                    texCoin[i][j]->srcRect.x += texCoin[i][j]->WidthTex / 10;
                    if(texCoin[i][j]->srcRect.x >= texCoin[i][j]->WidthTex){
                        texCoin[i][j]->srcRect.x = 0;   
                    }
                } 
            } 
        }
    }
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++){
            if(arr[i][j] == 1) {
                texCoin[i][j]->Draw();
            } 
        }    
    }
}

void Coin::takeScore(Player * player){
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++){
            if(arr[i][j] == 1) {
                if(texCoin[i][j]->collideTo(player->texPlayer)) {
                    Score += 5;
                    Mix_PlayChannel(0, Game::soundEffectGetCoin, 0);
                    texCoin[i][j]->dstRect = {-40, -40, -40, -40};    
                }
            } 
        } 
    }
}