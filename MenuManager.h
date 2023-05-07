#pragma once

#include "TextureManager.h"
#include <string>

class MenuManager {
public:
    MenuManager();
    ~MenuManager();
    
    bool needmenu();
    bool needsettings();
    bool running();
    bool needbgrmusic();
    bool needchangedifficulty();
    bool needchangeplayer();
    int difficulty();
    int colortype();

    void init();
    void clickStart();
    void clickSettings();
    void showSettings();
    void clickExit(); 
    void clickChangeDifficulty();
    void showDifficulty(); 
    void clickChangePlayer();
    void showPlayer();
    void turnBackinGame();
    void clickContactUs();
    void showBgMenu();

    void Clean();
private:
    bool needMenu = true;
    bool needSettings = false;
    bool isRunning = true;
    bool needBgrMusic = true;
    bool needChangeDifficulty = false;
    bool needChangePlayer = false;
    bool needFullscreen = false;

    int Difficulty = 1;
    int frameTimeMenu = 0;
    int colorType = 1;
};