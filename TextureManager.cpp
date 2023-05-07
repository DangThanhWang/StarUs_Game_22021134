#include "TextureManager.h"
#include "game.h"

TTF_Font * TextureManager::font;
SDL_Color TextureManager::colorWhite;
SDL_Color TextureManager::colorPurple;
SDL_Color TextureManager::colorLavender;
SDL_Color TextureManager::colorSkyBlue;

TextureManager::TextureManager() {}

TextureManager::TextureManager(const char * filename){
    SDL_Surface * tmpSurface = IMG_Load(filename);
    Texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
	SDL_QueryTexture(Texture, NULL, NULL, &WidthTex, &HeightTex);
}

TextureManager::~TextureManager(){
	SDL_DestroyTexture(Texture);
}

void TextureManager::LoadImageTex(const char * filename){
	SDL_Surface * tmpSurface = IMG_Load(filename);
    Texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void TextureManager::Draw(){
    SDL_RenderCopy(Game::renderer, Texture, &srcRect, &dstRect);
} 

void TextureManager::Draw2(){
	SDL_RenderCopy(Game::renderer, Texture, NULL, &dstRect);
}

bool TextureManager::collideTo(TextureManager * TexOther){
	int left1 = dstRect.x;
	int left2 = TexOther->dstRect.x; 
	int right1 = dstRect.x + dstRect.w;
	int right2 = TexOther->dstRect.x + TexOther->dstRect.w;
	int top1 = dstRect.y;
	int top2 = TexOther->dstRect.y;
	int bottom1 = dstRect.y + dstRect.h;
	int bottom2 = TexOther->dstRect.y + TexOther->dstRect.h;

	if(bottom1 < top2) return false;
	if(top1 > bottom2) return false;
	if(right1 < left2) return false;
	if(left1 > right2) return false;
    return true;
}

bool TextureManager::circularCollision(TextureManager * TexOther){
	int x1 = dstRect.x + dstRect.w / 2;
	int y1 = dstRect.x + dstRect.h / 2;
	int x2 = TexOther->dstRect.x + TexOther->dstRect.w / 2;
	int y2 = TexOther->dstRect.y + TexOther->dstRect.h / 2;

	int distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if(distance <= (dstRect.w / 2 + TexOther->dstRect.w / 2) || distance <= (dstRect.h / 2 + TexOther->dstRect.h / 2)) return true;
	else return false;
}

bool TextureManager::collideToMouse(){
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse, &yMouse);
	if(xMouse < dstRect.x) return false;
	if(yMouse < dstRect.y) return false;
	if(xMouse > dstRect.x + dstRect.w) return false;
	if(yMouse > dstRect.y + dstRect.h) return false;
	return true;
}

void TextureManager::LoadTexFont(const char * texString, SDL_Color color){
	SDL_Surface * sur = TTF_RenderText_Solid(font, texString, color);
	Texture = SDL_CreateTextureFromSurface(Game::renderer, sur);
	SDL_FreeSurface(sur);
}