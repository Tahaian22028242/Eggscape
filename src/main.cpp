#include "header/resourcesPath.hpp"

Platform platforms[4] = {{0}, {1}, {2}, {3}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2, platforms[0].getY() - player.getHeight(), 26, 32);
ScoreManager scoreManager = ScoreManager();

bool titleScreen = true;
bool playCoinFX = false;

void resetGame() { // Used to reset the game, including the player's score, position and the platforms.
    scoreManager.resetScore();
    
    for (int i = 0; i < 4; i++)
        platforms[i] = Platform(i);
    
    player.setVelocity(0, 0);
    player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2);
    player.setY(platforms[0].getY() - player.getHeight());
}

// Game's base logic #1: Check if the egg collides with the platform and the coin.
void checkPlayerCollision() {
    bool onPlatform = false;
    
    for (int i = 0; i < 4; i++) {
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
            scoreManager.addScore(1);
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

int main(int args, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    if (!InitSDL(window, renderer) || !InitAudio() || !InitTTF()) {
        return -1;
    }

    srand(time(NULL));
    
    scoreManager.resetScore();
    const char* highscore = scoreManager.getHighScoreString().c_str();
    //sprintf(highscore, "BEST: %d", highscoreInt);

    int mouseDownX = 0;
    int mouseDownY = 0;
    
    int lavaY = screenHeight - 32;
    double timer = 0; // Used to animate the lava.
    double splashTimer = 0; // Used to display the splash screen for a few seconds.
    
    bool firstTime = true;
    bool playedSplash = false; // Used to play the splash sound effect only once.
    bool playedSelect = false;

    SDL_Texture* playerSprite = loadTexture(playerImagePath, renderer);
    SDL_Texture* lavaSprite = loadTexture(lavaImagePath, renderer);
    SDL_Texture* platformSprite = loadTexture(platformImagePath, renderer);
    SDL_Texture* coinSprite = loadTexture(coinImagePath, renderer);
    SDL_Texture* scoreBoxSprite = loadTexture(scoreBoxImagePath, renderer);
    SDL_Texture* logo = loadTexture(logoImagePath, renderer);
    SDL_Texture* splashEggSprite = loadTexture(splashEggImagePath, renderer);

    Mix_Chunk* fxLaunch = loadSound(fxLaunchPath);
    Mix_Chunk* fxClick = loadSound(fxClickPath);
    Mix_Chunk* fxDeath = loadSound(fxDeathPath);
    Mix_Chunk* fxCoin = loadSound(fxCoinPath);
    Mix_Chunk* fxSplash = loadSound(fxSplashPath);
    Mix_Chunk* fxSelect = loadSound(fxSelectPath);

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
        
        SDL_PumpEvents(); // Update the mouse state
        SDL_GetMouseState(&mouse_x, &mouse_y); // Get the mouse's position
        
        // TODO: Vsync instead
        SDL_Delay(12);
        
        if (titleScreen) { // Display the title screen
            if (splashTimer > 120) { 
                if (!playedSelect) { // Play the select sound effect only once.
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
                
                Draw_Font(renderer, "EGG-SCAPE!", screenWidth/2 - 54, screenHeight/2 + 3, 108, 32, 32, {213, 128, 90});
                
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
                    
                    player.setVelocity((double)velocityX*0.08, (double)velocityY*0.08);
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
                // SDL_Rect platformSprite_rect = { platforms[i].getX(), platforms[i].getY(), 100, 32 };
                // SDL_RenderCopy(renderer, platformSprite, NULL, &platformSprite_rect);
                renderSprite(platformSprite, renderer, platforms[i].getX(), platforms[i].getY(), 100, 32);
                
                if (platforms[i].getHasCoin()) {
                    // SDL_Rect coinSprite_rect = { platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24 };
                    // SDL_RenderCopy(renderer, coinSprite, NULL, &coinSprite_rect);
                    renderSprite(coinSprite, renderer, platforms[i].getCoinX(), platforms[i].getCoinY(), 24, 24);
                }
            }
            
            // SDL_Rect playerSprite_rect = { player.getX(), player.getY(), 32, 32 };
            // SDL_RenderCopy(renderer, playerSprite, NULL, &playerSprite_rect);
            renderSprite(playerSprite, renderer, player.getX(), player.getY(), 32, 32);
            
            // SDL_Rect lavaSprite_rect = { 0, lavaY, 800, 48 };
            // SDL_RenderCopy(renderer, lavaSprite, NULL, &lavaSprite_rect);
            renderSprite(lavaSprite, renderer, 0, lavaY, 800, 48);
            
            // SDL_Rect scoreBoxSprite_rect = { 17, 17, 102, 70 };
            // SDL_RenderCopy(renderer, scoreBoxSprite, NULL, &scoreBoxSprite_rect);
            renderSprite(scoreBoxSprite, renderer, 17, 17, 102, 70);            
            
            Draw_Font(renderer, scoreManager.getScore().c_str(), 28, 20, 75, 64, 64, {0, 0, 0});
            Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), 17, 90, 74, 32, 32, {0, 0, 0});
            
            SDL_RenderPresent(renderer);
        }
       
    }

    // Cleanup resources
    cleanupTexture(playerSprite);
    cleanupTexture(lavaSprite);
    cleanupTexture(platformSprite);
    cleanupTexture(coinSprite);
    cleanupTexture(scoreBoxSprite);
    cleanupTexture(logo);
    cleanupTexture(splashEggSprite);

    cleanupSound(fxLaunch);
    cleanupSound(fxClick);
    cleanupSound(fxDeath);
    cleanupSound(fxCoin);
    cleanupSound(fxSplash);
    cleanupSound(fxSelect);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cleanupSystem();
   
    return 0;
}