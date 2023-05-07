#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Player.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "Ghost.h"
#include "MenuManager.h"
#include "Coin.h"
#include "Bomb.h"


using namespace std;

class Game {
public:
    Game();
    ~Game();
    void init(const char * title, int xpos, int ypos, int width, int height);
    void initObject();
    void initMenu();
    void runMusic();

    void runVideoIntro();

    void handleMenu();
    void showSettings();
    void showDifficulty();
    void showPlayer();

    void returnOriginalPosition();
    void returnNextPosition();
    void handleEvent();
    void playerPlay();
    void ghostPlay();
    void handleWhenLostGame();
    void handleWhenWinGame();
    void render();
    void clean();

    bool running();
    bool needsettings();
    bool needmenu();
    bool needbgrmusic();
    bool lostgame();
    bool wingame();
    bool video();
    bool needchangedifficulty();
    bool needchangeplayer();
    bool neednextlevel();

    static float deltaTime;
    static float frameTime;

    static SDL_Window * window;
    static SDL_Renderer * renderer;
    static SDL_Event event;
    static Mix_Music * backGroundMenuMusic;
    static Mix_Music * backGroundGameMusic;
    static Mix_Chunk * soundEffect;
    static Mix_Chunk * soundEffectGetCoin;
    static Mix_Chunk * soundEffectClick;
private:
    bool needSettings;
    bool needMenu;
    bool isRunning;
    bool playerDie;
    bool needBgrMusic = true;
    bool lostGame = false;
    bool winGame = false;
    bool Video = true;
    bool needChangeDifficulty = false;
    bool needChangePlayer = false;
    bool needNextLevel = false;

    int i = 0;
    int difficulty = 1;
    float moveSpeedGhost;

    string score;
};