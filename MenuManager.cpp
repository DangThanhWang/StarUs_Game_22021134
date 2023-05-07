#include "MenuManager.h"
#include "game.h"

TextureManager * texBackgroundMenu1;
TextureManager * texBackgroundMenu2;
TextureManager * texBackgroundMenu3;
TextureManager * texBackgroundMenu4;

TextureManager * texPlayerMenu;
TextureManager * buttonStart;
TextureManager * buttonSettings;
TextureManager * buttonDifficulty;
TextureManager * buttonContactUs;
TextureManager * buttonGamePlayer;
TextureManager * texTurnBack;
TextureManager * buttonQuitGame;
TextureManager * texTurnBackinGame;
TextureManager * buttonMusicOn;
TextureManager * buttonMusicOff;

TextureManager * easy;
TextureManager * medium;
TextureManager * hard;

TextureManager * chooseColorPlayer;
TextureManager * buttonLeft;
TextureManager * buttonRight;

TextureManager * buttonFullscreenOff;
TextureManager * buttonFullscreenOn;

MenuManager::MenuManager() {}
MenuManager::~MenuManager() {}

void MenuManager::init(){
    texBackgroundMenu1 = new TextureManager("data/bgMenu4.png");
    texBackgroundMenu1->srcRect = {35, 5, 430, 430};
    texBackgroundMenu1->dstRect = {200, 100, 400, 400};

    texBackgroundMenu2 = new TextureManager("data/bgMenu13.png");

    texBackgroundMenu3 = new TextureManager("data/bgMenu12.png");
    texBackgroundMenu3->srcRect = {0, 0, 1200, 800};
    texBackgroundMenu3->dstRect = {0, 0, 1200, 800};

    texBackgroundMenu4 = new TextureManager("data/bgMenu14.png");

    texPlayerMenu = new TextureManager("data/us.png");
    texPlayerMenu->srcRect = {0, 0, 80, 80};
    texPlayerMenu->dstRect = {360, 260, 80, 80};

    buttonStart = new TextureManager();
    buttonStart->LoadTexFont("START GAME", TextureManager::colorSkyBlue);
    buttonStart->dstRect = {800, 100, 250, 60};

    buttonDifficulty = new TextureManager();
    buttonDifficulty->LoadTexFont("DIFFICULTY", TextureManager::colorSkyBlue);
    buttonDifficulty->dstRect = {800, 180, 250, 60};

    buttonGamePlayer = new TextureManager();
    buttonGamePlayer->LoadTexFont("GAME PLAYER", TextureManager::colorSkyBlue);
    buttonGamePlayer->dstRect = {800, 260, 250, 60};

    buttonSettings = new TextureManager();
    buttonSettings->LoadTexFont("SETTINGS", TextureManager::colorSkyBlue);
    buttonSettings->dstRect = {800, 340, 250, 60};

    buttonContactUs = new TextureManager();
    buttonContactUs->LoadTexFont("CONTACT US", TextureManager::colorSkyBlue);
    buttonContactUs->dstRect = {800, 420, 250, 60};

    buttonQuitGame = new TextureManager();
    buttonQuitGame->LoadTexFont("QUIT GAME", TextureManager::colorSkyBlue);
    buttonQuitGame->dstRect = {800, 500, 250, 60};

    texTurnBack = new TextureManager();
    texTurnBack->LoadTexFont("TURN BACK", TextureManager::colorSkyBlue);

    texTurnBackinGame = new TextureManager();
    texTurnBackinGame->LoadTexFont("TURN HOME", TextureManager::colorSkyBlue);

    buttonMusicOn = new TextureManager();
    buttonMusicOn->LoadTexFont("MUSIC: ON", TextureManager::colorSkyBlue);
    buttonMusicOn->dstRect = {800, 400, 200, 50};

    buttonMusicOff = new TextureManager();
    buttonMusicOff->LoadTexFont("MUSIC: OFF", TextureManager::colorSkyBlue);
    buttonMusicOff->dstRect = {0, 0, 0, 0};

    easy = new TextureManager();
    easy->LoadTexFont("EASY", TextureManager::colorSkyBlue);
    easy->dstRect = {800, 100, 200, 50};

    medium = new TextureManager();
    medium->LoadTexFont("MEDIUM", TextureManager::colorSkyBlue);
    medium->dstRect = {800, 200, 200, 50};

    hard = new TextureManager();
    hard->LoadTexFont("HARD", TextureManager::colorSkyBlue);
    hard->dstRect = {800, 300, 200, 50};

    chooseColorPlayer = new TextureManager("data/us2.png");
    chooseColorPlayer->srcRect = {80, 0, 80, 80};
    chooseColorPlayer->dstRect = {560, 360, 80, 80};

    buttonLeft = new TextureManager();
    buttonLeft->LoadTexFont("LEFT", TextureManager::colorWhite);
    buttonLeft->dstRect = {250, 400, 150, 70};

    buttonRight = new TextureManager();
    buttonRight->LoadTexFont("RIGHT", TextureManager::colorWhite);
    buttonRight->dstRect = {800, 400, 150, 70};

    buttonFullscreenOff = new TextureManager();
    buttonFullscreenOff->LoadTexFont("FULLSCREEN: OFF", TextureManager::colorSkyBlue);
    buttonFullscreenOff->dstRect = {0, 0, 0, 0};

    buttonFullscreenOn = new TextureManager();
    buttonFullscreenOn->LoadTexFont("FULLSCREEN: ON", TextureManager::colorSkyBlue);
    buttonFullscreenOff->dstRect = {800, 200, 200, 50};
}

bool MenuManager::needmenu() {
    return needMenu;
}

bool MenuManager::needsettings() {
    return needSettings;
}

bool MenuManager::running() {
    return isRunning;
}

bool MenuManager::needbgrmusic(){
    return needBgrMusic;
}

bool MenuManager::needchangedifficulty(){
    return needChangeDifficulty;
}

bool MenuManager::needchangeplayer(){
    return needChangePlayer;
}

int MenuManager::difficulty() {
    return Difficulty;
}

int MenuManager::colortype(){
    return colorType;
}

void MenuManager::clickStart(){
    showBgMenu();
    if(buttonStart->collideToMouse()){
        SDL_SetTextureColorMod(buttonStart->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT) {
            needMenu = false;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } 
    else {
        SDL_SetTextureColorMod(buttonStart->Texture, 255, 255, 255);
    }

    buttonStart->Draw2();
}

void MenuManager::clickSettings(){
    if(buttonSettings->collideToMouse()) {
        SDL_SetTextureColorMod(buttonSettings->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT) {
            needSettings = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(buttonSettings->Texture, 255, 255, 255);
    }
    buttonSettings->Draw2();
}

void MenuManager::showSettings(){
    SDL_RenderCopy(Game::renderer, texBackgroundMenu4->Texture, NULL, NULL);
    texTurnBack->dstRect = {500, 700, 200, 50};
    if(texTurnBack->collideToMouse()){
        SDL_SetTextureColorMod(texTurnBack->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            needSettings = false;
            needMenu = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        } 
    } else {
        SDL_SetTextureColorMod(texTurnBack->Texture, 255, 255, 255);
    }
    
    if(buttonFullscreenOff->collideToMouse()){
        SDL_SetTextureColorMod(buttonFullscreenOff->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            SDL_SetWindowFullscreen(Game::window, SDL_WINDOW_FULLSCREEN);
            needFullscreen = true;
        }
    } else {
        SDL_SetTextureColorMod(buttonFullscreenOff->Texture, 255, 255, 255);
    }
    if(buttonFullscreenOn->collideToMouse()){
        SDL_SetTextureColorMod(buttonFullscreenOn->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            SDL_SetWindowFullscreen(Game::window, 0);
            SDL_SetWindowSize(Game::window, 1200, 800);
            needFullscreen = false;
        }
    } else {
        SDL_SetTextureColorMod(buttonFullscreenOn->Texture, 255, 255, 255);
    }

    if(needFullscreen) {
        buttonFullscreenOff->dstRect = {0, 0, 0, 0};
        buttonFullscreenOn->dstRect = {800, 200, 200, 50};
        buttonFullscreenOn->Draw2();
    } else {
        buttonFullscreenOn->dstRect = {0, 0, 0, 0};
        buttonFullscreenOff->dstRect = {800, 200, 200, 50};
        buttonFullscreenOff->Draw2(); 
    }

    if(buttonMusicOn->collideToMouse() && needBgrMusic == true){
        SDL_SetTextureColorMod(buttonMusicOn->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_HaltMusic();
            needBgrMusic = false;
        }
    } else {
        SDL_SetTextureColorMod(buttonMusicOn->Texture, 255, 255, 255);
    }

    if(buttonMusicOff->collideToMouse() && needBgrMusic == false) {
        SDL_SetTextureColorMod(buttonMusicOff->Texture, 0, 0, 255);
        if( Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT) {
            if(!Mix_PlayingMusic()){
				Mix_PlayMusic(Game::backGroundMenuMusic, -1);
			} else if (Mix_PausedMusic()){
				Mix_ResumeMusic();
			} else {
		    	Mix_PauseMusic();
			}
            needBgrMusic = true;
        }
    } else {
        SDL_SetTextureColorMod(buttonMusicOff->Texture, 255, 255, 255);
    }
    if(needBgrMusic) {
        buttonMusicOff->dstRect = {0, 0, 0, 0};
        buttonMusicOn->dstRect = {800, 400, 200, 50};
        buttonMusicOn->Draw2();
    } else {
        buttonMusicOff->dstRect = {800, 400, 200, 50};
        buttonMusicOn->dstRect = {0, 0, 0, 0};
        buttonMusicOff->Draw2();
    }

    SDL_RenderCopy(Game::renderer, texTurnBack->Texture, NULL, &texTurnBack->dstRect);
}

void MenuManager::clickChangeDifficulty(){
    if(buttonDifficulty->collideToMouse()){
        SDL_SetTextureColorMod(buttonDifficulty->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            needChangeDifficulty = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(buttonDifficulty->Texture, 255, 255, 255);
    }
    buttonDifficulty->Draw2();
}

void MenuManager::showDifficulty(){
    SDL_RenderCopy(Game::renderer, texBackgroundMenu2->Texture, NULL, NULL);
    texTurnBack->dstRect = {500, 700, 200, 50};
    if(texTurnBack->collideToMouse()){
        SDL_SetTextureColorMod(texTurnBack->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            needChangeDifficulty = false;
            needMenu = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        } 
    } else {
        SDL_SetTextureColorMod(texTurnBack->Texture, 255, 255, 255);
    }

    if(easy->collideToMouse()){
        SDL_SetTextureColorMod(easy->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Difficulty = 1;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(easy->Texture, 255, 255, 255);
    }

    if(medium->collideToMouse()){
        SDL_SetTextureColorMod(medium->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Difficulty = 2;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(medium->Texture, 255, 255, 255);
    }

    if(hard->collideToMouse()){
        SDL_SetTextureColorMod(hard->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Difficulty = 3;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(hard->Texture, 255, 255, 255);
    }

    switch (Difficulty)
    {
    case 1:
        SDL_SetTextureColorMod(easy->Texture, 0, 0, 255);
        break;
    case 2:
        SDL_SetTextureColorMod(medium->Texture, 0, 0, 255);
        break;
    case 3:
        SDL_SetTextureColorMod(hard->Texture, 0, 0, 255);
        break;
    default:
        break;
    }
    texTurnBack->Draw2();
    easy->Draw2();
    medium->Draw2();
    hard->Draw2();
}

void MenuManager::clickChangePlayer(){
    if(buttonGamePlayer->collideToMouse()){
        SDL_SetTextureColorMod(buttonGamePlayer->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            needChangePlayer = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(buttonGamePlayer->Texture, 255, 255, 255);
    }
    buttonGamePlayer->Draw2();
}

void MenuManager::showPlayer(){
    texBackgroundMenu1->dstRect = {400, 200, 400, 400};
    texTurnBack->dstRect = {500, 700, 200, 50};

    frameTimeMenu += 1;
    if(frameTimeMenu % 2){
        texBackgroundMenu1->srcRect.x += 500;
        texPlayerMenu->srcRect.x += 80;
        if(texBackgroundMenu1->srcRect.x >= 3000) {
            texBackgroundMenu1->srcRect.x = 35;
            texBackgroundMenu1->srcRect.y += 440;
            if(texBackgroundMenu1->srcRect.y >= 4400) {
                texBackgroundMenu1->srcRect.y = 5;
            }
        }
        if(texPlayerMenu->srcRect.x >= texPlayerMenu->WidthTex){
            texPlayerMenu->srcRect.x = 0;
        }
    }
    frameTimeMenu+=1;
    if(frameTimeMenu == 10000) frameTimeMenu = 0;
    
    texBackgroundMenu3->Draw();
    texBackgroundMenu1->Draw();
    if(texTurnBack->collideToMouse()){
        SDL_SetTextureColorMod(texTurnBack->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            needChangePlayer = false;
            needMenu = true;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        } 
    } else {
        SDL_SetTextureColorMod(texTurnBack->Texture, 255, 255, 255);
    }
    if(buttonRight->collideToMouse()){
        SDL_SetTextureColorMod(buttonRight->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            colorType += 1;
            if(colorType > 12) colorType = 1;
            chooseColorPlayer->srcRect.x += 240;
            if(chooseColorPlayer->srcRect.x >= chooseColorPlayer->WidthTex) {
                chooseColorPlayer->srcRect.x = 80;
            }
        }
    } else {
        SDL_SetTextureColorMod(buttonRight->Texture, 255, 255, 255);
    }

    if(buttonLeft->collideToMouse()){
        SDL_SetTextureColorMod(buttonLeft->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            colorType -= 1;
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            if(colorType < 1) colorType = 12;
            chooseColorPlayer->srcRect.x -= 240;
            if(chooseColorPlayer->srcRect.x < 0) {
                chooseColorPlayer->srcRect.x = chooseColorPlayer->WidthTex - 160;
            }
        }
    } else {
        SDL_SetTextureColorMod(buttonLeft->Texture, 255, 255, 255);
    }
    if(frameTimeMenu % 6 == 0) {
        chooseColorPlayer->srcRect.x += 80;
        if(chooseColorPlayer->srcRect.x >= colorType * 240) {
            chooseColorPlayer->srcRect.x = (colorType - 1) * 240;
        }
    }
    texTurnBack->Draw2();
    chooseColorPlayer->Draw();
    buttonLeft->Draw2();
    buttonRight->Draw2();
}

void MenuManager::clickContactUs(){
    if(buttonContactUs->collideToMouse()){
        SDL_SetTextureColorMod(buttonContactUs->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            SDL_OpenURL("https://www.facebook.com/profile.php?id=100044308152218");
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
        }
    } else {
        SDL_SetTextureColorMod(buttonContactUs->Texture, 255, 255, 255);
    }
    buttonContactUs->Draw2();
}

void MenuManager::clickExit(){
    if(buttonQuitGame->collideToMouse()){
        SDL_SetTextureColorMod(buttonQuitGame->Texture, 0, 0, 250);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            isRunning = false;
        }
    } else {
        SDL_SetTextureColorMod(buttonQuitGame->Texture, 255, 255, 255);
    }
    buttonQuitGame->Draw2();
}

void MenuManager::turnBackinGame(){
    texTurnBackinGame->dstRect = {900, 670, 200, 50};
    if(texTurnBackinGame->collideToMouse()){
        SDL_SetTextureColorMod(texTurnBackinGame->Texture, 0, 0, 255);
        if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT){
            Mix_PlayChannel(-1, Game::soundEffectClick, 0);
            needMenu = true;
        }
    } else {
        SDL_SetTextureColorMod(texTurnBackinGame->Texture, 255, 255, 255);
    }
    texTurnBackinGame->Draw2();
}

void MenuManager::showBgMenu(){
    SDL_RenderCopy(Game::renderer, texBackgroundMenu2->Texture, NULL, NULL);
}

void MenuManager::Clean(){
    texBackgroundMenu1->~TextureManager();
    texBackgroundMenu2->~TextureManager();
    texBackgroundMenu3->~TextureManager();
    texPlayerMenu->~TextureManager();
    buttonStart->~TextureManager();
    buttonSettings->~TextureManager();
    buttonDifficulty->~TextureManager();
    buttonContactUs->~TextureManager();
    buttonGamePlayer->~TextureManager();
    texTurnBack->~TextureManager();
    buttonQuitGame->~TextureManager();
    texTurnBackinGame->~TextureManager();
    buttonMusicOn->~TextureManager();
    buttonMusicOff->~TextureManager();
    easy->~TextureManager();
    medium->~TextureManager();
    hard->~TextureManager();
}