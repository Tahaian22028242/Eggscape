#include "header/resourcesPath.hpp"

Platform platforms[4] = {{0}, {1}, {2}, {3}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2, platforms[0].getY() - player.getHeight()/*, 26, 32*/);
ScoreManager scoreManager = ScoreManager();

bool hasBorder = false;
// Used to play the coin sound effect only once.
bool playCoinFX = false;

void resetGame() { // Used to reset the game, including the player's score, position and the platforms.
    player.setBorderAvailable(hasBorder);
    player.setLife(player.getLife());    
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
        // Check if the egg collides with the coin.
        if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
            scoreManager.addScore(coinValue);
            platforms[i].setHasCoin(false);
            playCoinFX = true;
        }
        
        // Check if the egg collides with the platform.
        if (player.getX() + 1 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) { 
            if (player.getY() > platforms[i].getY() + platforms[i].getHeight()/2) { // If the egg is below the platform.
                player.setVelocity(player.getVelocity().x, 5);
            } 
            else if (player.getY() + player.getHeight() <  platforms[i].getY() + platforms[i].getHeight()) { // If the egg is above the platform.   
                onPlatform = true;
                player.setY(platforms[i].getY() - player.getHeight());
                player.setY(player.getY() + 1);

                // Make the egg follow the platform's movement.
                if (platforms[i].getIsMoving() == 1) 
                    player.setX(player.getX() - platformSpeed);
                else if (platforms[i].getIsMoving() == 2) 
                    player.setX(player.getX() + platformSpeed);
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

    srand(time(NULL)); // Seed the random number generator
    
    scoreManager.resetScore();
    const char* highscore = scoreManager.getHighScoreString().c_str();

    int mouseDownX = 0;
    int mouseDownY = 0;
    
    int lavaY = screenHeight - 32;
    double timer = 0; // Used to animate the lava.
    double splashTimer = 0; // Used to display the splash screen for a few seconds.
    
    bool firstTime = true; // Used to prevent the egg from launching when the game starts.
    bool playedSplash = false; // Used to play the splash sound effect only once.
    bool playedSelect = false; // Used to play the select sound effect only once.

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
    int soundVolume = MIX_MAX_VOLUME / 2; // Initial sound volume (50%)
    Mix_Volume(-1, soundVolume);

    // Load the random background music
    bool randomMusic = rand() % 2;
    Mix_Music* backgroundMusic = nullptr;
    if (randomMusic) 
        backgroundMusic = loadMusic(music1Path);
    else 
        backgroundMusic = loadMusic(music2Path);

    int musicVolume = MIX_MAX_VOLUME / 2; // Initial music volume (50%)
    Mix_VolumeMusic(musicVolume);
    if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
        cerr << "Failed to play music: " << Mix_GetError() << endl;
    }

    if (fxLaunch == nullptr || fxClick == nullptr || fxDeath == nullptr || fxCoin == nullptr || fxSplash == nullptr || fxSelect == nullptr) {
        cerr << "Failed to load audio: " << Mix_GetError() << endl;
        return 1;
    }

    bool draggingMusic = false;
    bool draggingSound = false;
    
    bool quit = false;
    bool titleScreen = true;
    bool gamePaused = false;
    bool gameStarted = false;
    bool settingsScreen = false;
    //bool tutorialScreen = false;
    
    bool mouse_down = false;
    int mouse_x, mouse_y;
    
    while (!quit) {
        SDL_Event event;
        bool mouse_released = false;
        bool mouse_pressed = false;
        
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
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
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    else if (event.key.keysym.sym == SDLK_p) {
                        gamePaused = !gamePaused;
                    }
                    else if (event.key.keysym.sym == SDLK_r) {
                        resetGame();
                    }
                    else if (event.key.keysym.sym == SDLK_b) {
                        hasBorder = !hasBorder;
                        player.setBorderAvailable(hasBorder);
                    }
                } break;
            }
        }
      
        SDL_PumpEvents(); // Update the mouse state
        SDL_GetMouseState(&mouse_x, &mouse_y); // Get the mouse's position
        // TODO: Vsync instead
        SDL_Delay(12); // 60 FPS
        
        if (gamePaused) {
            // TODO: Display a pause screen
            // SDL_RenderClear(renderer);
            Mix_PauseMusic(); // Pause the music
            //renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30, 400, 90);
            Draw_Font(renderer, "PAUSED!", screenWidth/2 - 30, screenHeight/2 - 150/2, 60, 32, 64, {213, 128, 90});
            Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), screenWidth/2 - 37, screenHeight/2 + 10, 74, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "Press 'P' to continue", screenWidth/2 - 134, screenHeight/2 + 50, 268, 32, 32, {178, 150, 125});

            Draw_Font(renderer, "Settings", screenWidth/2 - 30, screenHeight/2 + 100, 60, 32, 32, {178, 150, 125});
            if (mouse_down &&
                 mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                 mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) {
                Mix_PlayChannel(-1, fxSelect, 0);
                settingsScreen = true;
                gamePaused = false;
                // mouseDownX = mouse_x;
                // mouseDownY = mouse_y;
            }
            SDL_RenderPresent(renderer);
            continue;
        } else {
            // Resume the music
            Mix_ResumeMusic();
        }
  
        
        if (titleScreen) { // Display the title screen
            if (splashTimer < 120) { 
                if (!playedSplash) { // Play the splash sound effect only once.
                    Mix_PlayChannel(-1, fxSplash, 0);
                    playedSplash = true;
                }
                
                SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
                SDL_RenderClear(renderer);
                
                renderSprite(splashEggSprite, renderer, screenWidth/2 - 16, screenHeight/2 - 16 - 23, 32, 32);
                Draw_Font(renderer, "EGG-SCAPE!", screenWidth/2 - 54, screenHeight/2 + 3, 108, 32, 32, {213, 128, 90});
                Draw_Font(renderer, "JUMP FOR YOUR LIFE!", screenWidth/2 - 100, screenHeight/2 + 40, 200, 32, 32, {178, 150, 125});
                      
                SDL_RenderPresent(renderer);
                
                splashTimer += 1;
            }
            else {
                // if (SDL_WaitEvent(&event)) {
                //     if (event.type == SDL_MOUSEMOTION) {
                //         SDL_GetMouseState(&mouse_x, &mouse_y);
                //         cout << "Mouse position: " << mouse_x << " " << mouse_y << endl;
                //     }
                //     else if (event.type == SDL_KEYDOWN) {
                //         if (event.key.keysym.sym == SDLK_p) {
                //             gamePaused = !gamePaused;
                //             if (gamePaused) {
                //                 Mix_PauseMusic();
                //             } else {
                //                 Mix_ResumeMusic();
                //             }
                //         }
                //     }
                // }       
                if (!playedSelect) { // Play the select sound effect only once.
                    Mix_PlayChannel(-1, fxSelect, 0);
                    playedSelect = true;
                }
                
                SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
                SDL_RenderClear(renderer); 
                
                renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30, 400, 90);
                Draw_Font(renderer, highscore, screenWidth/2 - 37, screenHeight/2 + 10, 74, 32, 32, {0, 0, 0});
                
                // Render start button
                if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                     mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132)
                    Draw_Font(renderer, "Start", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Start", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {178, 150, 125});

                // TODO: Implement the tutorial screen

                // Render settings button
                if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                     mouse_y > screenHeight/2 + 150 && mouse_y < screenHeight/2 + 182)
                    Draw_Font(renderer, "Settings", screenWidth/2 - 30, screenHeight/2 + 150, 60, 32, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Settings", screenWidth/2 - 30, screenHeight/2 + 150, 60, 32, 32, {178, 150, 125});

                SDL_RenderPresent(renderer);
                
                // if (mouse_pressed) { /* This is the old code that checks if the mouse is pressed (anywhere) to start the game. */
                //     Mix_PlayChannel(-1, fxSelect, 0);
                //     titleScreen = false;
                //     mouseDownX = mouse_x;
                //     mouseDownY = mouse_y;
                // }

                if (mouse_pressed &&
                     mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                     mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    gameStarted = true;
                }

                if (mouse_pressed &&
                     mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                     mouse_y > screenHeight/2 + 150 && mouse_y < screenHeight/2 + 182) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    settingsScreen = true;
                }
            }            
        }

        if (settingsScreen) {
            SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
            SDL_RenderClear(renderer);
        
            // Draw labels
            Draw_Font(renderer, "SETTINGS", screenWidth/2 - 60, screenHeight/2 - 200, 120, 32, 64, {213, 128, 90});

            std::string musicChoosingTitle = "Choose Background Music:";
            Draw_Font(renderer, musicChoosingTitle.c_str(), screenWidth/2 - 150 - 32, screenHeight/2 - 150, 
                      musicChoosingTitle.length()*10, 32, 32, {178, 150, 125});

            std::string currentMusic = randomMusic ? "Music 1" : "Music 2";
            int musicNameLength = ((int)currentMusic.length()-1)*10;
            Draw_Font(renderer, currentMusic.c_str(), screenWidth/2 + 110 + 32 + 8 - 32, screenHeight/2 - 150, 
                      musicNameLength, 32, 32, {213, 128, 90});

            // Draw left arrow
            if (mouse_x > screenWidth/2 + 110 - 32 && mouse_x < screenWidth/2 + 110 &&
                 mouse_y > screenHeight/2 - 150 && mouse_y < screenHeight/2 - 150 + 32)
                Draw_Font(renderer, "<", screenWidth/2 + 110 - 32, screenHeight/2 - 150, 32, 32, 32, {213, 128, 90});
            else 
                Draw_Font(renderer, "<", screenWidth/2 + 110 - 32, screenHeight/2 - 150, 32, 32, 32, {178, 150, 125});

            // Draw right arrow
            if (mouse_x > screenWidth/2 + 210 + 8 - 32 && mouse_x < screenWidth/2 + 210 + 8 &&
                 mouse_y > screenHeight/2 - 150 && mouse_y < screenHeight/2 - 150 + 32)
                Draw_Font(renderer, ">", screenWidth/2 + 110 + 32 + 8 + musicNameLength + 8 - 32, screenHeight/2 - 150, 32, 32, 32, {213, 128, 90});
            else 
                Draw_Font(renderer, ">", screenWidth/2 + 110 + 32 + 8 + musicNameLength + 8 - 32, screenHeight/2 - 150, 32, 32, 32, {178, 150, 125});

            // Calculate length of the rest titles(e.g. "Music Volume;" ~ 12*10 = 120) with the same way as the music choosing title(text length(-=1 if necessary) * 10). 

            Draw_Font(renderer, "Music Volume:", screenWidth/2 - 150, screenHeight/2 - 100, 120, 32, 32, {178, 150, 125});
            Draw_Font(renderer, "Sound Volume:", screenWidth/2 - 150, screenHeight/2 - 50, 120, 32, 32, {178, 150, 125});

            Draw_Font(renderer, "Border:", screenWidth/2 - 100, screenHeight/2, 60, 32, 32, {178, 150, 125});
            std::string borderStatus = hasBorder ? "ON!" : "Off!";
            if (hasBorder)
                Draw_Font(renderer, borderStatus.c_str(), screenWidth/2 + 50, screenHeight/2, (int)borderStatus.length()*8, 32, 32, {213, 128, 90});
            else
                Draw_Font(renderer, borderStatus.c_str(), screenWidth/2 + 50, screenHeight/2, (int)borderStatus.length()*8, 32, 32, {178, 150, 125});

            // bool keyConfigScreen = false;
            // Draw_Font(renderer, "Key Config", screenWidth/2 - 100, screenHeight/2 + 50, 60, 32, 32, {178, 150, 125}); 
    
            if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                 mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132)

                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {213, 128, 90});
            else 
                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {178, 150, 125});
        
            // Draw volume lines
            SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
            SDL_RenderDrawLine(renderer, screenWidth/2 + 20, screenHeight/2 - 82, screenWidth/2 + 170, screenHeight/2 - 82);
            SDL_RenderDrawLine(renderer, screenWidth/2 + 20, screenHeight/2 - 32, screenWidth/2 + 170, screenHeight/2 - 32);
        
            // Draw draggable rectangles
            SDL_Rect musicRect = {screenWidth/2 - 50 + (musicVolume * 200 / MIX_MAX_VOLUME), screenHeight/2 - 87, 10, 10};
            SDL_Rect soundRect = {screenWidth/2 - 50 + (soundVolume * 200 / MIX_MAX_VOLUME), screenHeight/2 - 37, 10, 10};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &musicRect);
            SDL_RenderFillRect(renderer, &soundRect);
        
            SDL_RenderPresent(renderer);
        
            if (mouse_pressed) {
                
                // Handle music selection
                if (((mouse_x > screenWidth/2 + 110 - 32 && mouse_x < screenWidth/2 + 110) &&
                    (mouse_y > screenHeight/2 - 150 && mouse_y < screenHeight/2 - 150 + 32)) ||
                    ((mouse_x > screenWidth/2 + 210 + 8 - 32 && mouse_x < screenWidth/2 + 210 + 8) && 
                    (mouse_y > screenHeight/2 - 150 && mouse_y < screenHeight/2 - 150 + 32)))
                {
                    randomMusic = !randomMusic;
                    if (randomMusic) {
                        Mix_FreeMusic(backgroundMusic);
                        backgroundMusic = loadMusic(music1Path);
                    } else {
                        Mix_FreeMusic(backgroundMusic);
                        backgroundMusic = loadMusic(music2Path);
                    }
                    Mix_PlayMusic(backgroundMusic, -1);
                }
                
                // Handle border selection
                else if (mouse_x > screenWidth/2 + 50 && mouse_x < screenWidth/2 + 70 &&
                    mouse_y > screenHeight/2 && mouse_y < screenHeight/2 + 32) 
                {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    hasBorder = !hasBorder;
                    player.setBorderAvailable(hasBorder);
                }

                // Handle back button
                else if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                         mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) 
                {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    if (!gamePaused) {
                        settingsScreen = false;
                        titleScreen = true;
                    } else {
                        Mix_PlayChannel(-1, fxSelect, 0);
                        settingsScreen = false;
                        gamePaused = true;
                    }
                }
            }

            if (mouse_down) {
                // Handle volume adjustment
                if (mouse_x > musicRect.x && mouse_x < musicRect.x + musicRect.w &&
                    mouse_y > musicRect.y && mouse_y < musicRect.y + musicRect.h) 
                {
                    draggingMusic = true;
                } 
                else if (mouse_x > soundRect.x && mouse_x < soundRect.x + soundRect.w &&
                         mouse_y > soundRect.y && mouse_y < soundRect.y + soundRect.h)
                {
                    draggingSound = true;
                }
            } else {
                draggingMusic = false;
                draggingSound = false;
            }
        
            if (draggingMusic) {
                int new_x = std::min(std::max(mouse_x, screenWidth/2 - 50), screenWidth/2 + 150);
                musicVolume = (new_x - (screenWidth/2 - 50)) * MIX_MAX_VOLUME / 200;
                Mix_VolumeMusic(musicVolume);
            }

            if (draggingSound) {
                int new_x = std::min(std::max(mouse_x, screenWidth/2 - 50), screenWidth/2 + 150);
                soundVolume = (new_x - (screenWidth/2 - 50)) * MIX_MAX_VOLUME / 200;
                Mix_Volume(-1, soundVolume); // Set volume for all channels
            }
        }

        if (gameStarted) {
            if (playCoinFX) {
                Mix_PlayChannel(-1, fxCoin, 0);
                playCoinFX = false;
            }
  
            // Game's base logic #3: Using the mouse's press and release to control the egg's movement.
            if (mouse_pressed && player.isOnPlatform()) {
                Mix_PlayChannel(-1, fxClick, 0);
                mouseDownX = mouse_x;
                mouseDownY = mouse_y;
            }
            
            if (mouse_released && player.isOnPlatform()) {
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
            // Game's base logic #4: Check if the egg is out of bounds. 
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
            
            if (mouse_down && player.isOnPlatform()) {
                SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
                SDL_RenderDrawLine(
                    renderer,
                    mouseDownX + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    mouseDownY + (player.getY() - mouseDownY) + (player.getHeight()/2),
                    mouse_x + (player.getX() - mouseDownX) + (player.getWidth()/2),
                    mouse_y + (player.getY() - mouseDownY) + (player.getHeight()/2)
                );
            }
    
            for (int i = 0; i < 4; i++) {
                renderSprite(platformSprite, renderer, 
                    platforms[i].getX(), platforms[i].getY(), platforms[i].getWidth(), platforms[i].getHeight());
                
                if (platforms[i].getHasCoin()) {
                    renderSprite(coinSprite, renderer, 
                        platforms[i].getCoinX(), platforms[i].getCoinY(), coinWidth, coinHeight);
                }
            }
            
            renderSprite(playerSprite, renderer, player.getX(), player.getY(), 32, 32);
            renderSprite(lavaSprite, renderer, 0, lavaY, 800, 48);            
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

    cleanupMusic(backgroundMusic);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cleanupSystem();
   
    return 0;
}

// #include "header/resourcesPath.hpp"

// Platform platforms[4] = {{0}, {1}, {2}, {3}};
// Player player(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2, platforms[0].getY() - player.getHeight()/*, 26, 32*/);
// Coin coins[4] = {{0, platforms[0]}, {1, platforms[1]},
//                  {2, platforms[2]}, {3, platforms[3]}};
// ScoreManager scoreManager = ScoreManager();

// bool titleScreen = true;
// bool playCoinFX = false;

// bool hasBorder = false;

// void resetGame() { // Used to reset the game, including the player's score, position and the platforms.
//     player.setBorderAvailable(hasBorder);    
//     scoreManager.resetScore();
    
//     for (int i = 0; i < 4; i++)
//         platforms[i] = Platform(i);
    
//     player.setVelocity(0, 0);
//     player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2);
//     player.setY(platforms[0].getY() - player.getHeight());
// }

// // Game's base logic #1: Check if the egg collides with the platform and the coin.
// void checkPlayerCollision() {
//     bool onPlatform = false;
    
//     for (int i = 0; i < 4; i++) {
//         // Check if the egg collides with the coin.
//         if (platforms[i].getHasCoin() && player.getX() + player.getWidth() - 3 > platforms[i].getCoinX() && player.getX() + 3 < platforms[i].getCoinX() + 24 && player.getY() + player.getHeight() - 3 > platforms[i].getCoinY() && player.getY() + 3 < platforms[i].getCoinY() + 24) {
//             scoreManager.addScore(coinValue);
//             platforms[i].setHasCoin(false);
//             playCoinFX = true;
//         }

//         if (player.getX() == coins[i].getX() && player.getY() == coins[i].getY()) {
//             scoreManager.addScore(coinValue);
//             coins[i].setIsAvailable(false);
//             playCoinFX = true;
//         }
        
//         // Check if the egg collides with the platform.
//         if (player.getX() + 1 < platforms[i].getX() + platforms[i].getWidth() && player.getX() + player.getWidth() > platforms[i].getX() && player.getY() + player.getHeight() >= platforms[i].getY() && player.getY() < platforms[i].getY() + platforms[i].getHeight()) { 
//             if (player.getY() > platforms[i].getY() + platforms[i].getHeight()/2) { // If the egg is below the platform.
//                 player.setVelocity(player.getVelocity().x, 5);
//             } 
//             else if (player.getY() + player.getHeight() <  platforms[i].getY() + platforms[i].getHeight()) { // If the egg is above the platform.   
//                 onPlatform = true;
//                 player.setY(platforms[i].getY() - player.getHeight());
//                 player.setY(player.getY() + 1);

//                 // Make the egg follow the platform's movement.
//                 if (platforms[i].getIsMoving() == 1) 
//                     player.setX(player.getX() - platformSpeed);
//                 else if (platforms[i].getIsMoving() == 2) 
//                     player.setX(player.getX() + platformSpeed);
//             }
//         }
//     }
//     player.setOnPlatform(onPlatform);
// } // End of Game's base logic #1

// int main(int args, char* argv[]) {
//     SDL_Window* window = nullptr;
//     SDL_Renderer* renderer = nullptr;
    
//     if (!InitSDL(window, renderer) || !InitAudio() || !InitTTF()) {
//         return -1;
//     }

//     srand(time(NULL));
    
//     scoreManager.resetScore();
//     const char* highscore = scoreManager.getHighScoreString().c_str();

//     int mouseDownX = 0;
//     int mouseDownY = 0;
    
//     int lavaY = screenHeight - 32;
//     double timer = 0; // Used to animate the lava.
//     double splashTimer = 0; // Used to display the splash screen for a few seconds.
    
//     bool firstTime = true;
//     bool playedSplash = false; // Used to play the splash sound effect only once.
//     bool playedSelect = false;

//     SDL_Texture* playerSprite = loadTexture(playerImagePath, renderer);
//     SDL_Texture* lavaSprite = loadTexture(lavaImagePath, renderer);
//     SDL_Texture* platformSprite = loadTexture(platformImagePath, renderer);
//     SDL_Texture* coinSprite = loadTexture(coinImagePath, renderer);
//     SDL_Texture* scoreBoxSprite = loadTexture(scoreBoxImagePath, renderer);
//     SDL_Texture* logo = loadTexture(logoImagePath, renderer);
//     SDL_Texture* splashEggSprite = loadTexture(splashEggImagePath, renderer);

//     Mix_Chunk* fxLaunch = loadSound(fxLaunchPath);
//     Mix_Chunk* fxClick = loadSound(fxClickPath);
//     Mix_Chunk* fxDeath = loadSound(fxDeathPath);
//     Mix_Chunk* fxCoin = loadSound(fxCoinPath);
//     Mix_Chunk* fxSplash = loadSound(fxSplashPath);
//     Mix_Chunk* fxSelect = loadSound(fxSelectPath);

//     if (fxLaunch == nullptr || fxClick == nullptr || fxDeath == nullptr || fxCoin == nullptr || fxSplash == nullptr || fxSelect == nullptr) {
//         cerr << "Failed to load audio: " << Mix_GetError() << endl;
//         return 1;
//     }
    
//     bool quit = false;
//     bool gamePaused = false;

//     bool mouse_down = false;
    
//     int mouse_x, mouse_y;
    
//     while (!quit) {
//         SDL_Event event;
//         bool mouse_released = false;
//         bool mouse_pressed = false;
        
//         while (SDL_PollEvent(&event)) {
//             switch(event.type) {
//                 case SDL_QUIT: {
//                     quit = true;
//                 } break;
//                 case SDL_MOUSEBUTTONDOWN: {
//                     mouse_down = true;
//                     mouse_pressed = true;
//                 } break;
//                 case SDL_MOUSEBUTTONUP: {
//                     mouse_down = false;
//                     mouse_released = true;
//                 } break;
//                 case SDL_KEYDOWN: {
//                     if (event.key.keysym.sym == SDLK_ESCAPE) {
//                         quit = true;
//                     }
//                     else if (event.key.keysym.sym == SDLK_p) {
//                         gamePaused = !gamePaused;
//                     }
//                     else if (event.key.keysym.sym == SDLK_r) {
//                         resetGame();
//                     }
//                     else if (event.key.keysym.sym == SDLK_b) {
//                         hasBorder = !hasBorder;
//                         player.setBorderAvailable(hasBorder);
//                     }
//                 } break;
//             }
//         }

//         if (gamePaused) {
//             continue;
//         }
        
//         SDL_PumpEvents(); // Update the mouse state
//         SDL_GetMouseState(&mouse_x, &mouse_y); // Get the mouse's position
        
//         // TODO: Vsync instead
//         SDL_Delay(12);
        
//         if (titleScreen) { // Display the title screen
//             if (splashTimer > 120) { 
//                 if (!playedSelect) { // Play the select sound effect only once.
//                     Mix_PlayChannel(-1, fxSelect, 0);
//                     playedSelect = true;
//                 }
                
//                 SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
//                 SDL_RenderClear(renderer); 
                
//                 renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30, 400, 90);
                
//                 Draw_Font(renderer, highscore, screenWidth/2 - 37, screenHeight/2 + 10, 74, 32, 32, {0, 0, 0});
//                 Draw_Font(renderer, "CLICK ANYWHERE TO BEGIN", screenWidth/2 - 134, screenHeight/2 + 50, 268, 32, 32, {178, 150, 125});
                
//                 SDL_RenderPresent(renderer);
                
//                 if (mouse_pressed) {
//                     Mix_PlayChannel(-1, fxSelect, 0);
//                     titleScreen = false;
//                     mouseDownX = mouse_x;
//                     mouseDownY = mouse_y;
//                 }
//             }
//             else {
//                 if (!playedSplash) {
//                     Mix_PlayChannel(-1, fxSplash, 0);
//                     playedSplash = true;
//                 }
                
//                 SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
//                 SDL_RenderClear(renderer);
                
//                 renderSprite(splashEggSprite, renderer, screenWidth/2 - 16, screenHeight/2 - 16 - 23, 32, 32);
//                 Draw_Font(renderer, "EGG-SCAPE!", screenWidth/2 - 54, screenHeight/2 + 3, 108, 32, 32, {213, 128, 90});
                      
//                 SDL_RenderPresent(renderer);
                
//                 splashTimer += 1;
//             }            
//         } 
//         else {
//             if (playCoinFX) {
//                 Mix_PlayChannel(-1, fxCoin, 0);
//                 playCoinFX = false;
//             }
  
//             // Game's base logic #3: Using the mouse's press and release to control the egg's movement.
//             if (mouse_pressed && player.isOnPlatform()) {
//                 Mix_PlayChannel(-1, fxClick, 0);
//                 mouseDownX = mouse_x;
//                 mouseDownY = mouse_y;
//             }
            
//             if (mouse_released && player.isOnPlatform()) {
//                 if (firstTime) {
//                     firstTime = false;
//                 }
//                 else {
//                     Mix_PlayChannel(-1, fxLaunch, 0);
                    
//                     if (player.isOnPlatform())
//                         player.setY(player.getY() - 1);
                    
//                     int velocityX = mouse_x - mouseDownX;
//                     int velocityY = mouse_y - mouseDownY;
                    
//                     player.setVelocity((double)velocityX*0.08, (double)velocityY*0.08);
//                 }
//             } // End of Game's base logic #3
        
//             checkPlayerCollision();
//             player.updatePosition();
//             // Game's base logic #4: Check if the egg is out of bounds. 
//             if (player.getY() > screenHeight) {
//                 Mix_PlayChannel(-1, fxDeath, 0);
//                 resetGame();
//             }

//             for (int i = 0; i < 4; i++) {
//                 platforms[i].updatePosition();
//                 coins[i].updatePosition();
//             }
            
//             lavaY = screenHeight - 43 - sin(timer) * 5;
//             timer += 0.05;
            
//             SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
//             SDL_RenderClear(renderer);
            
//             if (mouse_down && player.isOnPlatform()) {
//                 SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
//                 SDL_RenderDrawLine(
//                     renderer,
//                     mouseDownX + (player.getX() - mouseDownX) + (player.getWidth()/2),
//                     mouseDownY + (player.getY() - mouseDownY) + (player.getHeight()/2),
//                     mouse_x + (player.getX() - mouseDownX) + (player.getWidth()/2),
//                     mouse_y + (player.getY() - mouseDownY) + (player.getHeight()/2)
//                 );
//             }
    
//             for (int i = 0; i < 4; i++) {
//                 renderSprite(platformSprite, renderer, 
//                     platforms[i].getX(), platforms[i].getY(), platforms[i].getWidth(), platforms[i].getHeight());
                
//                 if (platforms[i].getHasCoin()) {
//                     renderSprite(coinSprite, renderer, 
//                             platforms[i].getCoinX(), platforms[i].getCoinY(), coinWidth, coinHeight);
//                 }

//                 if (coins[i].getIsAvailable()) {
//                     renderSprite(coinSprite, renderer, 
//                             coins[i].getX(), coins[i].getY(), coinWidth, coinHeight);
//                 }
//             }
            
//             renderSprite(playerSprite, renderer, player.getX(), player.getY(), 32, 32);
//             renderSprite(lavaSprite, renderer, 0, lavaY, 800, 48);            
//             renderSprite(scoreBoxSprite, renderer, 17, 17, 102, 70);            
            
//             Draw_Font(renderer, scoreManager.getScore().c_str(), 28, 20, 75, 64, 64, {0, 0, 0});
//             Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), 17, 90, 74, 32, 32, {0, 0, 0});
            
//             SDL_RenderPresent(renderer);
//         }
       
//     }

//     // Cleanup resources
//     cleanupTexture(playerSprite);
//     cleanupTexture(lavaSprite);
//     cleanupTexture(platformSprite);
//     cleanupTexture(coinSprite);
//     cleanupTexture(scoreBoxSprite);
//     cleanupTexture(logo);
//     cleanupTexture(splashEggSprite);

//     cleanupSound(fxLaunch);
//     cleanupSound(fxClick);
//     cleanupSound(fxDeath);
//     cleanupSound(fxCoin);
//     cleanupSound(fxSplash);
//     cleanupSound(fxSelect);

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     cleanupSystem();
   
//     return 0;
// }