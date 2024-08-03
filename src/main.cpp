#include <iostream>
#include <filesystem>
#include <cmath>
#include <ctime>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "header/player.hpp"
#include "header/platform.hpp"

using namespace std;

Platform platforms[4] = {{0}, {1}, {2}, {3}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2, platforms[0].getY() - player.getHeight(), 26, 32);

bool titleScreen = true;
bool playCoinFX = false;

char score[32];
int scoreInt = 0;

char highscore[32];
int LoadHighScore() { // Used to load the highscore from the file.
    FILE *scorefile = fopen("highscore.bin", "rb");
    
    if (!scorefile)
        return 0;
    
    int ret;
    fread(&ret, sizeof(int), 1, scorefile);
    fclose(scorefile);
    
    return ret;
}
int highscoreInt = LoadHighScore();

void SaveHighScore(int val) { // Used to save the highscore to the file.
    FILE *scorefile = fopen("highscore.bin", "wb");
    
    fwrite(&val, sizeof(int), 1, scorefile);
    fclose(scorefile);
}

void resetScore() { // Used to reset the score and highscore.
    scoreInt = 0;
    sprintf(score, "00%d", scoreInt);
    SaveHighScore(highscoreInt);
}

void resetGame() { // Used to reset the game, including the player's score, position and the platforms.
    resetScore();
    
    for (int i = 0; i < 4; i++)
        platforms[i] = Platform(i);
    
    player.setVelocity(0, 0);
    player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2);
    player.setY(platforms[0].getY() - player.getHeight());
}

void addScore(int amount) { // Used in collision check to update the score and highscore.
    scoreInt += amount;
    
    if (scoreInt < 10)
        sprintf(score, "00%d", scoreInt);
    else if (scoreInt < 100)
        sprintf(score, "0%d", scoreInt);
    else
        sprintf(score, "%d", scoreInt);
    
    if (scoreInt > highscoreInt) {
        highscoreInt = scoreInt;
        sprintf(highscore, "BEST: %d", highscoreInt);
    }
}

// Game's base logic #1: Check if the egg collides with the platform and the coin.
void checkPlayerCollision() {
    bool onPlatform = false;
    
    for (int i = 0; i < 4; i++) {
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
            addScore(1);
            platforms[i].setHasCoin(false);
            playCoinFX = true;
        }
        
        if (player.getX() + 1 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) {
            if (player.getY() > platforms[i].getY() + platforms[i].getHeight()/2) {
                player.setVelocity(player.getVelocity().x, 5);
            } 
            else if (player.getY() + player.getHeight() <  platforms[i].getY() + platforms[i].getHeight()) {    
                onPlatform = true;
                player.setY(platforms[i].getY() - player.getHeight());
                player.setY(player.getY() + 1);
            }
        }
    }
    player.setOnPlatform(onPlatform);
} // End of Game's base logic #1

void Draw_Font(SDL_Renderer *renderer, const char *str, int x, int y, int width, int height, int size, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont(fontPath, size);
    
    SDL_Surface* message_surf = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, message_surf);
    SDL_Rect Message_rect = {x, y, width, height};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(message_surf);
    TTF_CloseFont(font);
}

int main(int args, char* argv[]) {
    srand(time(NULL));
    
    // resetScore();
    // sprintf(highscore, "BEST: %d", highscoreInt);
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    int mouseDownX = 0;
    int mouseDownY = 0;
    
    int lavaY = screenHeight - 32;
    double timer = 0; 
    double splashTimer = 0;
    
    bool firstTime = true;
    bool playedSplash = false;
    bool playedSelect = false;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        cerr << "Failed to initialize: " << SDL_GetError() << endl;
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow(
        "Terri-Fried",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenWidth, screenHeight,
        SDL_WINDOW_OPENGL
    );
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Surface* egg = IMG_Load(playerImagePath);
    if (egg == nullptr) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return 1;
    }
    SDL_SetWindowIcon(window, egg);
    SDL_FreeSurface(egg);
    
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
    // SetMasterVolume(0.3f);
    
    SDL_Surface* playerSprite_surf = IMG_Load(playerImagePath);
    SDL_Surface* lavaSprite_surf = IMG_Load(lavaImagePath);
    SDL_Surface* platformSprite_surf = IMG_Load(platformImagePath);
    SDL_Surface* coinSprite_surf = IMG_Load(coinImagePath);
    SDL_Surface* scoreBoxSprite_surf = IMG_Load(scoreBoxImagePath);
    SDL_Surface* logo_surf = IMG_Load(logoImagePath);
    SDL_Surface* splashEggSprite_surf = IMG_Load(splashEggImagePath);
    if (playerSprite_surf == nullptr || lavaSprite_surf == nullptr || platformSprite_surf == nullptr || coinSprite_surf == nullptr || scoreBoxSprite_surf == nullptr || logo_surf == nullptr || splashEggSprite_surf == nullptr) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return 1;
    }
    
    SDL_Texture* playerSprite = SDL_CreateTextureFromSurface(renderer, playerSprite_surf);
    SDL_Texture* lavaSprite = SDL_CreateTextureFromSurface(renderer, lavaSprite_surf);
    SDL_Texture* platformSprite = SDL_CreateTextureFromSurface(renderer, platformSprite_surf);
    SDL_Texture* coinSprite = SDL_CreateTextureFromSurface(renderer, coinSprite_surf);
    SDL_Texture* scoreBoxSprite = SDL_CreateTextureFromSurface(renderer, scoreBoxSprite_surf);
    SDL_Texture* logo = SDL_CreateTextureFromSurface(renderer, logo_surf);
    SDL_Texture* splashEggSprite = SDL_CreateTextureFromSurface(renderer, splashEggSprite_surf);
    
    Mix_Chunk* fxLaunch = Mix_LoadWAV(fxLaunchPath); 
    Mix_Chunk* fxClick = Mix_LoadWAV(fxClickPath); 
    Mix_Chunk* fxDeath = Mix_LoadWAV(fxDeathPath); 
    Mix_Chunk* fxCoin = Mix_LoadWAV(fxCoinPath); 
    Mix_Chunk* fxSplash = Mix_LoadWAV(fxSplashPath);
    Mix_Chunk* fxSelect = Mix_LoadWAV(fxSelectPath);
    if (fxLaunch == nullptr || fxClick == nullptr || fxDeath == nullptr || fxCoin == nullptr || fxSplash == nullptr || fxSelect == nullptr) {
        cerr << "Failed to load audio: " << Mix_GetError() << endl;
        return 1;
    }
    
    bool quit = false;
    
    bool mouse_down = false;
    
    int mouse_x, mouse_y;
    
    while (!quit) {
        SDL_Event e;
        bool mouse_released = false;
        bool mouse_pressed = false;
        
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;
                case SDL_MOUSEBUTTONDOWN: {
                    mouse_down = true;
                    mouse_pressed = true;
                } break;
                case SDL_MOUSEBUTTONUP: {
                    mouse_down = false;
                    mouse_released = true;
                } break;
            }
        }
        
        SDL_PumpEvents();
        SDL_GetMouseState(&mouse_x, &mouse_y);
        
        // TODO: Vsync instead
        SDL_Delay(12);
        
        if (titleScreen) {
            if (splashTimer > 120) {
                if (!playedSelect) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    playedSelect = true;
                }
                
                SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
                SDL_RenderClear(renderer);
                
                SDL_Rect logo_rect = { screenWidth/2 - 200, screenHeight/2 - 45 - 30, 400, 90 };
                SDL_RenderCopy(renderer, logo, NULL, &logo_rect);
                
                Draw_Font(renderer, highscore, screenWidth/2 - 37, screenHeight/2 + 10, 74, 32, 32, {0, 0, 0});
                Draw_Font(renderer, "CLICK ANYWHERE TO BEGIN", screenWidth/2 - 134, screenHeight/2 + 50, 268, 32, 32, {178, 150, 125});
                
                SDL_RenderPresent(renderer);
                
                if (mouse_pressed) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    mouseDownX = mouse_x;
                    mouseDownY = mouse_y;
                }
            }
            else {
                if (!playedSplash) {
                    Mix_PlayChannel(-1, fxSplash, 0);
                    playedSplash = true;
                }
                
                SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
                SDL_RenderClear(renderer);
                
                Draw_Font(renderer, "POLYMARS", screenWidth/2 - 54, screenHeight/2 + 3, 108, 32, 32, {213, 128, 90});
                
                SDL_Rect splashEggSprite_rect = { screenWidth/2 - 16, screenHeight/2 - 16 - 23, 32, 32 };
                SDL_RenderCopy(renderer, splashEggSprite, NULL, &splashEggSprite_rect);
                
                SDL_RenderPresent(renderer);
                
                splashTimer += 1;
            }
        } 
        else {
            if (playCoinFX) {
                Mix_PlayChannel(-1, fxCoin, 0);
                playCoinFX = false;
            }
            
            // Game's base logic #3: Using the mouse's press and release to control the egg's movement.
            if (mouse_pressed && player.isOnGround()) {
                Mix_PlayChannel(-1, fxClick, 0);
                mouseDownX = mouse_x;
                mouseDownY = mouse_y;
            }
            
            if (mouse_released && player.isOnGround()) {
                if (firstTime) {
                    firstTime = false;
                }
                else {
                    Mix_PlayChannel(-1, fxLaunch, 0);
                    
                    if (player.isOnPlatform())
                        player.setY(player.getY() - 1);
                    
                    int velocityX = mouse_x - mouseDownX;
                    int velocityY = mouse_y - mouseDownY;
                    
                    player.setVelocity((double)velocityX*.08, (double)velocityY*.08);
                }
            } // End of Game's base logic #3
        
            checkPlayerCollision();
            player.updatePosition();
            
            if (player.getY() > screenHeight) {
                Mix_PlayChannel(-1, fxDeath, 0);
                resetGame();
            }
            for (int i = 0; i < 4; i++) {
                platforms[i].updatePosition();
            }
            
            lavaY = screenHeight - 43 - sin(timer) * 5;
            timer += 0.05;
            
            SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
            SDL_RenderClear(renderer);
            
            if (mouse_down && player.isOnGround()) {
                SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
                SDL_RenderDrawLine(
                    renderer,
                    mouseDownX + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    mouseDownY + (player.getY() - mouseDownY) + (player.getHeight()/2),
                    mouse_x + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    mouse_y + (player.getY() - mouseDownY) + (player.getHeight()/2)
                );
            }
            
            //DrawRectangle(player.getX(), player.getY(), player.getWidth(), player.getHeight(), WHITE);
            
            for (int i = 0; i < 4; i++) {
                SDL_Rect platformSprite_rect = { platforms[i].getX(), platforms[i].getY(), 100, 32 };
                SDL_RenderCopy(renderer, platformSprite, NULL, &platformSprite_rect);
                
                if (platforms[i].getHasCoin()) {
                    SDL_Rect coinSprite_rect = { platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24 };
                    SDL_RenderCopy(renderer, coinSprite, NULL, &coinSprite_rect);
                }
            }
            
            SDL_Rect playerSprite_rect = { player.getX(), player.getY(), 32, 32 };
            SDL_RenderCopy(renderer, playerSprite, NULL, &playerSprite_rect);
            
            SDL_Rect lavaSprite_rect = { 0, lavaY, 800, 48 };
            SDL_RenderCopy(renderer, lavaSprite, NULL, &lavaSprite_rect);
            
            SDL_Rect scoreBoxSprite_rect = { 17, 17, 102, 70 };
            SDL_RenderCopy(renderer, scoreBoxSprite, NULL, &scoreBoxSprite_rect);
            
            Draw_Font(renderer, score, 28, 20, 75, 64, 64, {0, 0, 0});
            Draw_Font(renderer, highscore, 17, 90, 74, 32, 32, {0, 0, 0});
            
            SDL_RenderPresent(renderer);
        }
       
    }

    SDL_DestroyTexture(playerSprite);
    SDL_DestroyTexture(lavaSprite);
    SDL_DestroyTexture(platformSprite);
    SDL_DestroyTexture(coinSprite);
    SDL_DestroyTexture(scoreBoxSprite);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(splashEggSprite);
    
    SDL_FreeSurface(playerSprite_surf);
    SDL_FreeSurface(lavaSprite_surf);
    SDL_FreeSurface(platformSprite_surf);
    SDL_FreeSurface(coinSprite_surf);
    SDL_FreeSurface(scoreBoxSprite_surf);
    SDL_FreeSurface(logo_surf);
    SDL_FreeSurface(splashEggSprite_surf);
    
    Mix_FreeChunk(fxClick);
    Mix_FreeChunk(fxLaunch);
    Mix_FreeChunk(fxDeath);
    Mix_FreeChunk(fxCoin);
    Mix_FreeChunk(fxSplash);
    Mix_FreeChunk(fxSelect);
    
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
   
    return 0;
}
