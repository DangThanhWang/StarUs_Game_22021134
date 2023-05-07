#include "game.h"
#include "game.cpp"
#include "TextureManager.h"
#include "TextureManager.cpp"
#include "Player.h"
#include "Player.cpp"
#include "MapManager.h"
#include "MapManager.cpp"
#include "Ghost.h"
#include "Ghost.cpp"
#include "MenuManager.h"
#include "MenuManager.cpp"
#include "Coin.h"
#include "Coin.cpp"
#include "Bomb.h"
#include "Bomb.cpp"

Game * game = NULL;

int main(int argc, char * argv [])
{
	int prevTime = 0;
	int currentTime = 0;
	Game::deltaTime = 0;
	
	game = new Game();
	game->init("StarUs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800);
	game->initObject();
	game->initMenu();

	game->runMusic();
	while(game->running() && game->video()){
		game->runVideoIntro();
	}

	while(game->running()){
		SDL_PollEvent(&Game::event);
		if(game->needbgrmusic()) {
			game->runMusic();
		}
		while(game->running() && game->needmenu()){
			game->handleMenu();
			while(game->running() && game->needsettings()) {
				game->showSettings();
			}
			while(game->running() && game->needchangedifficulty()){
				game->showDifficulty();
			}
			while(game->running() && game->needchangeplayer()){
				game->showPlayer();
			}	
		}
		if(!game->neednextlevel()){
			game->returnOriginalPosition();
		} else {
			game->returnNextPosition();
		}
		
		if(game->needbgrmusic()) {
			game->runMusic();
		}
		while(game->running() && !game->needmenu() && !game->neednextlevel()){	
			prevTime = currentTime;
			currentTime = SDL_GetTicks();
			Game::deltaTime = (currentTime - prevTime) / 1000.0f;

			game->handleEvent();
			game->playerPlay();
			game->ghostPlay();
			game->render();	
			while(game->running() && game->lostgame() && !game->needmenu()){
				game->handleWhenLostGame();
			}
			while(game->running() && game->wingame() && !game->needmenu() && !game->neednextlevel()){
				game->handleWhenWinGame();
			}	
		}
	}
	game->clean();
	return 0;
}