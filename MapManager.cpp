#include "MapManager.h"

TextureManager * Map::texMap;
SDL_Rect Map::barriers[31];

void Map::initMap(){
    barriers[0] = {40, 40, 160, 40};
	barriers[1] = {40, 80, 40, 40};
	barriers[2] = {240, 40, 360, 40};
	barriers[3] = {320, 80, 160, 80};
	barriers[4] = {640, 40, 120, 40};
	barriers[5] = {720, 80, 40, 120};
	barriers[6] = {120, 120, 160, 120};
	barriers[7] = {520, 120, 160, 120};
	barriers[8] = {40, 160, 40, 360};
	barriers[9] = {80, 280, 120, 200};
	barriers[10] = {200, 360, 120, 40};
	barriers[11] = {240, 280, 320, 40};
	barriers[12] = {320, 200, 160, 80};
	barriers[13] = {360, 360, 80, 40};
	barriers[14] = {480, 360, 120, 40};
	barriers[15] = {600, 280, 120, 200};
	barriers[16] = {720, 240, 40, 360};
	barriers[17] = {240, 440, 320, 40};
	barriers[18] = {320, 480, 160, 80};
	barriers[19] = {120, 520, 160, 120};
	barriers[20] = {520, 520, 160, 120};
	barriers[21] = {40, 560, 40, 200};
	barriers[22] = {80, 680, 120, 80};
	barriers[23] = {320, 600, 160, 80};
	barriers[24] = {240, 680, 320, 80};
	barriers[25] = {600, 680, 160, 80};
	barriers[26] = {720, 640, 40, 40};
	barriers[27] = {-100, -100, 1000, 100};
	barriers[28] = {-100, 800, 1000, 100};
	barriers[29] = {-100, -100, 100, 1000};
	barriers[30] = {800, -100, 1000, 1000};
	
	texMap = new TextureManager("data/bgGame6.png");
	texMap->dstRect = {0, 0, 800, 800};
	texMap->srcRect = {0, 0, 800, 800};
}

bool Map::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int left1 = x1;
	int left2 = x2;
	int right1 = x1 + w1;
	int right2 = x2 + w2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = y1 + h1;
	int bottom2 = y2 + h2;

	if(bottom1 <= top2) return false;
	if(top1 >= bottom2) return false;
	if(right1 <= left2) return false;
	if(left1 >= right2) return false;
	return true;
}

bool Map::canUp(SDL_Rect rectObject, int addedValue){
    for(int i = 0; i < 31; i++) {
        if(collision(rectObject.x, rectObject.y - addedValue, rectObject.w, rectObject.h, barriers[i].x, barriers[i].y, barriers[i].w, barriers[i].h)) 
        return false;
    }
    return true;
}

bool Map::canDown(SDL_Rect rectObject, int addedValue){
    for(int i = 0; i < 31; i++) {
        if(collision(rectObject.x, rectObject.y + addedValue, rectObject.w, rectObject.h, barriers[i].x, barriers[i].y, barriers[i].w, barriers[i].h)) 
        return false;
    }
    return true;
}

bool Map::canLeft(SDL_Rect rectObject, int addedValue){
    for(int i = 0; i < 31; i++) {
        if(collision(rectObject.x - addedValue, rectObject.y, rectObject.w, rectObject.h, barriers[i].x, barriers[i].y, barriers[i].w, barriers[i].h)) 
        return false;
    }
    return true;
}

bool Map::canRight(SDL_Rect rectObject, int addedValue){
    for(int i = 0; i < 31; i++) {
        if(collision(rectObject.x + addedValue, rectObject.y, rectObject.w, rectObject.h, barriers[i].x, barriers[i].y, barriers[i].w, barriers[i].h)) 
        return false;
    }
    return true;
}