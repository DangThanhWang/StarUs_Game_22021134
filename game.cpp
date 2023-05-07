#include "game.h"

SDL_Texture * TexVideo[4];
SDL_Rect src;
SDL_Rect dst;
string s;
int m = 1;
int j = 0;

Player * player;
Ghost * ghost1;
Ghost * ghost2;
Ghost * ghost3;

MenuManager * Menu;
Coin * coin;
Bomb * bom;

SDL_Event Game::event;

TextureManager * texScore;
TextureManager * texLost;
TextureManager * texWin;
TextureManager * buttonNextLevel;

float Game::deltaTime = 0;
float Game::frameTime = 0;

Mix_Music * Game::backGroundMenuMusic;
Mix_Music * Game::backGroundGameMusic;
Mix_Chunk * Game::soundEffect;
Mix_Chunk * Game::soundEffectGetCoin;
Mix_Chunk * Game::soundEffectClick;

SDL_Renderer * Game::renderer = nullptr;
SDL_Window * Game::window = nullptr;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char * title, int xpos, int ypos, int width, int height){
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0 && Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0){
        cout << "Subsystems initialised" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        if(window) {
            cout << "Window created" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer){
            cout << "Renderer created" << endl;
            SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
        }
        isRunning = true;
        
        needSettings = false;
        needMenu = true;
    } 
    else {
        isRunning = false;
    }
    Map::initMap();

    coin = new Coin();
    coin->init("data/coinAnimation4.png");
    bom = new Bomb();
    bom->init();
    
    TextureManager::font = TTF_OpenFont("data/font1.ttf", 40);
    TextureManager::colorWhite = {255, 255, 255, 255}; 
    TextureManager::colorPurple = {115, 43, 245, 255};
    TextureManager::colorLavender = {240, 155, 89, 255};
    TextureManager::colorSkyBlue = {115, 251, 253, 255};

    texScore = new TextureManager();

    texLost = new TextureManager();
    texLost->LoadTexFont("YOU LOST", TextureManager::colorSkyBlue);
    texLost->dstRect = {900, 250, 200, 50};

    texWin = new TextureManager();
    texWin->LoadTexFont("YOU WIN", TextureManager::colorSkyBlue);
    texWin->dstRect = {900, 250, 200, 50};

    buttonNextLevel = new TextureManager();
    buttonNextLevel->LoadTexFont("NEXT LEVEL", TextureManager::colorSkyBlue);
    buttonNextLevel->dstRect = {900, 450, 200, 50};

    backGroundMenuMusic = Mix_LoadMUS("data/backgroundMusic3.mp3");
    backGroundGameMusic = Mix_LoadMUS("data/backgroundMusic3.mp3");
    soundEffect = Mix_LoadWAV("data/soundEffect.wav");
    soundEffectGetCoin = Mix_LoadWAV("data/soundEffect3.wav");
    soundEffectClick = Mix_LoadWAV("data/soundEffect6.wav");
    
    for(int i = 1; i <= 3; i++){
        s = "data/Starus" + to_string(i) + ".png";
        TexVideo[i] = IMG_LoadTexture(renderer, s.c_str());
    }
    src = {90, 0, 972, 648};
}

void Game::initObject(){
    player = new Player();
    ghost1 = new Ghost();
    ghost2 = new Ghost();
    ghost3 = new Ghost();

    player->initPlayer("data/us.png");
    ghost1->initGhost("data/us.png");
    ghost2->initGhost("data/us.png");
    ghost3->initGhost("data/us.png");
}

void Game::initMenu(){
    Menu = new MenuManager();
    Menu->init();
}

void Game::runMusic(){
    if(!Mix_PlayingMusic()){
		Mix_PlayMusic(backGroundMenuMusic, -1);
	} else if (Mix_PausedMusic()){
		Mix_ResumeMusic();
	}
}

bool Game::running(){
    return isRunning;
}

bool Game::needsettings(){
    return needSettings;
}

bool Game::needmenu(){
    return needMenu;
}

bool Game::needbgrmusic(){
    return needBgrMusic;
}

bool Game::lostgame(){
    return lostGame;
}

bool Game::wingame(){
    return winGame;
}

bool Game::needchangedifficulty(){
    return needChangeDifficulty;
}

bool Game::needchangeplayer(){
    return needChangePlayer;
}

bool Game::neednextlevel(){
    return needNextLevel;
}

void Game::handleMenu(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
        return;
    }

    needMenu = Menu->needmenu();
    needSettings = Menu->needsettings();
    needChangeDifficulty = Menu->needchangedifficulty();
    needChangePlayer = Menu->needchangeplayer();
    isRunning = Menu->running();

    SDL_RenderClear(renderer);
    Menu->clickStart();
    Menu->clickSettings();
    Menu->clickExit();
    Menu->clickChangeDifficulty();
    Menu->clickContactUs();
    Menu->clickChangePlayer();
    SDL_RenderPresent(renderer);
}

void Game::showSettings(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }

    needSettings = Menu->needsettings();
    needBgrMusic = Menu->needbgrmusic();
    
    SDL_RenderClear(renderer);
    Menu->showSettings();
    SDL_RenderPresent(renderer);
}

void Game::showDifficulty(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }
    needChangeDifficulty = Menu->needchangedifficulty();
    difficulty = Menu->difficulty();

    SDL_RenderClear(renderer);
    Menu->showDifficulty();
    SDL_RenderPresent(renderer);
}

void Game::showPlayer(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }

    needChangePlayer = Menu->needchangeplayer();

    SDL_RenderClear(renderer);
    Menu->showPlayer();
    SDL_RenderPresent(renderer);
}

void Game::returnOriginalPosition(){
    coin->returnPosition();
    coin->Score = 0;
    lostGame = false;
    winGame = false;

    player->texPlayer->dstRect = {765, 765, 35, 35};
    player->texPlayer->srcRect = {(Menu->colortype() - 1) * 240, 0, 80, 80};

    ghost1->texGhost->dstRect = {80, 80, 40, 40};
    ghost2->texGhost->dstRect = {80, 480, 40, 40};
    ghost3->texGhost->dstRect = {480, 80, 40, 40};

    moveSpeedGhost = 1;
    ghost1->returnNewMoveSpeed(moveSpeedGhost);
    ghost2->returnNewMoveSpeed(moveSpeedGhost);
    ghost3->returnNewMoveSpeed(moveSpeedGhost);
}

void Game::returnNextPosition(){
    coin->returnPosition();
    lostGame = false;
    winGame = false;
    needNextLevel = false;

    player->texPlayer->dstRect = {765, 765, 35, 35};
    player->texPlayer->srcRect = {(Menu->colortype() - 1) * 240, 0, 80, 80};

    ghost1->texGhost->dstRect = {80, 80, 40, 40};
    ghost2->texGhost->dstRect = {80, 480, 40, 40};
    ghost3->texGhost->dstRect = {480, 80, 40, 40};

    moveSpeedGhost += 0.5;
    ghost1->returnNewMoveSpeed(moveSpeedGhost);
    ghost2->returnNewMoveSpeed(moveSpeedGhost);
    ghost3->returnNewMoveSpeed(moveSpeedGhost);
}

void Game::handleEvent(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }
    needMenu = Menu->needmenu();
    Menu->turnBackinGame();
    needBgrMusic = Menu->needbgrmusic();
}

void Game::playerPlay(){
    player->Play(Menu->colortype());
    if(player->CollideToGhost(ghost1) || player->CollideToGhost(ghost2) || player->CollideToGhost(ghost3) || bom->collideTo(player)) {
        lostGame = true;
    }
    coin->takeScore(player);
    score = "Score: " + to_string(coin->score());
    texScore->LoadTexFont(score.c_str(), TextureManager::colorSkyBlue);
    texScore->dstRect = {900, 50, 200, 50};
    
    if(coin->score() % 960 == 0) {
        winGame = true;
    }
    bom->play(); 
}

void Game::ghostPlay(){
    if(difficulty == 1) {
        ghost1->AutoAIdirection(player->texPlayer->dstRect, 1);
        ghost2->AutoDirection(player->texPlayer->dstRect, 2);
        ghost3->AutoDirection(player->texPlayer->dstRect, 3);
    }
    if(difficulty == 2) {
        ghost1->AutoAIdirection(player->texPlayer->dstRect, 1);
        ghost2->AutoAIdirection(player->texPlayer->dstRect, 2);
        ghost3->AutoDirection(player->texPlayer->dstRect, 3);
    }
    if(difficulty == 3) {
        ghost1->AutoAIdirection(player->texPlayer->dstRect, 1);
        ghost2->AutoAIdirection(player->texPlayer->dstRect, 2);
        ghost3->AutoAIdirection(player->texPlayer->dstRect, 3);
    }
    ghost1->SetDirection();
    ghost1->Play();

    ghost2->SetDirection();
    ghost2->Play();

    ghost3->SetDirection();
    ghost3->Play();
}

void Game::render(){
    SDL_RenderClear(renderer);
    Menu->showBgMenu();
    Map::texMap->Draw();
    Menu->turnBackinGame();
    coin->coinRender();
    player->Render(); 
    ghost1->Render(); //cout << "1 "<< ghost1->texGhost->dstRect.x << " " << ghost1->texGhost->dstRect.y << endl;
    ghost2->Render(); //cout << "2 "<< ghost2->texGhost->dstRect.x << " " << ghost2->texGhost->dstRect.y << endl;
    ghost3->Render(); //cout << "3 "<< ghost3->texGhost->dstRect.x << " " << ghost3->texGhost->dstRect.y << endl;
    bom->Render();
    SDL_RenderCopy(renderer, texScore->Texture, NULL, &texScore->dstRect);
    SDL_RenderPresent(renderer);
}

void Game::handleWhenLostGame(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }
    SDL_RenderClear(renderer);
    Menu->showBgMenu();
    Map::texMap->Draw();
    Menu->turnBackinGame();
    texScore->Draw2();
    texLost->Draw2();
    SDL_RenderPresent(renderer);
    needMenu = Menu->needmenu();
}

void Game::handleWhenWinGame(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }
    if(buttonNextLevel->collideToMouse()){
        SDL_SetTextureColorMod(buttonNextLevel->Texture, 0, 0, 250);
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
            needNextLevel = true;
            needMenu = false;
        }
    } else {
        SDL_SetTextureColorMod(buttonNextLevel->Texture, 255, 255, 255);
    }
    SDL_RenderClear(renderer);
    Menu->showBgMenu();
    Map::texMap->Draw();
    Menu->turnBackinGame();
    texScore->Draw2();
    texWin->Draw2();
    buttonNextLevel->Draw2();
    SDL_RenderPresent(renderer);
    needMenu = Menu->needmenu();
}

void Game::clean(){
    for(int i = 0; i < 4; i++){
        SDL_DestroyTexture(TexVideo[i]);
    }
    Menu->Clean();
    player->Clean();
    ghost1->Clean();
    ghost2->Clean();
    ghost3->Clean();
    Mix_FreeMusic(backGroundMenuMusic);
    Mix_FreeMusic(backGroundGameMusic);
    Mix_FreeChunk(soundEffect);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    cout << "Game cleaned" << endl;
}


bool Game::video(){
    return Video;
}

void Game::runVideoIntro(){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        isRunning = false;
    }

    j++;
    if(j % 2 == 0 ) {
        src.x += 1152;
        if(src.x >= 5760){
            src.x = 90;
            src.y += 648;
            if(src.y >= 3888){
                src.y = 0;
                m++;
            }
        }
    }
    if(m < 4) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, TexVideo[m], &src, NULL);
        SDL_RenderPresent(renderer);
    } else {
        Video = false;
    }
}