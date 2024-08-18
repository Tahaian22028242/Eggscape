#include "header/resourcesPath.hpp"

Platform platforms[4] = {{0}, {1}, {2}, {3}};
Player player(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2, platforms[0].getY() - player.getHeight()/*, 26, 32*/);
ScoreManager scoreManager = ScoreManager();
Threat threat = Threat();
Shield shield = Shield();

bool hasBorder = false;
bool playCoinFX = false;
bool playDeathFX = false;
bool gameOver = false;
bool gameRestarted = false;

void resetGame() { // Used to reset the game, including the player's score, position and the platforms.
    if (gameOver || gameRestarted) {
        scoreManager.resetScore();
        player.setLife(playerMaxLife);
    }
    player.setLife(player.getLife());
    for (int i = 0; i < 4; i++) {
        platforms[i] = Platform(i);
    }
    player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2);
    player.setY(platforms[0].getY() - player.getHeight());
    player.setVelocity(0, 0);
    player.setOnPlatform(false);
    shield.setIsOnPlayer(false);
    threat.setIsAvailable(false);
    threat.setX(screenWidth - threat.getWidth());
    threat.setY(screenHeight - threat.getHeight());
    threat.setIsAvailable(true);
    threat.setMoveType(rand() % 2);
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

    // Check if the egg collides with the shield.
    if (shield.getIsOnPlayer() == false && player.getX() + player.getWidth() - 3 > shield.getX() && player.getX() + 3 < shield.getX() + shield.getWidth() &&
        player.getY() + player.getHeight() - 3 > shield.getY() && player.getY() + 3 < shield.getY() + shield.getHeight()) {

        shield.setIsOnPlayer(true);
    }

    // Check if the egg collides with the threat.
    if (player.getX() + player.getWidth() - 3 > threat.getX() && player.getX() + 3 < threat.getX() + threat.getWidth() && 
        player.getY() + player.getHeight() - 3 > threat.getY() && player.getY() + 3 < threat.getY() + threat.getHeight()) {

        playDeathFX = true;

        if (shield.getIsOnPlayer()) {
            shield.setIsOnPlayer(false);
        } else {
            player.setLife(player.getLife() - 1);
            if (player.getLife() <= 0) {
                gameOver = true;
            } else {
                threat.setIsAvailable(false);
                threat.setX(threat.getX());
                threat.setY(screenHeight - threat.getHeight());
                threat.setIsAvailable(true);
                threat.setMoveType(rand() % 2);
            }           
        }
    }

    // Check if the egg collides with the lava.
    if (player.getY() > screenHeight) {
        playDeathFX = true;
        player.setLife(player.getLife() - 1);
        if (player.getLife() <= 0) {
            gameOver = true;
        }  
        resetGame();
        // player.setY(0 - player.getHeight());
        // player.setX(platforms[0].getX() + platforms[0].getWidth()/2 - 26/2);
        // player.setVelocity(0, 0);
    }
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
    SDL_Texture* threatSprite = loadTexture(threatImagePath, renderer);
    SDL_Texture* shieldSprite = loadTexture(shieldImagePath, renderer);
    //SDL_Texture* armedPlayerSprite = loadTexture(armedPlayerImagePath, renderer);

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
    //bool toSettingsFromPause = false;
    //bool tutorialScreen = false;
    
    bool mouse_down = false;
    int mouse_x, mouse_y;

    Uint32 lastToggleTime = 0; // Used to prevent the player from toggling the border too quickly
    const Uint32 flickerInterval = 500; // Flicker interval in milliseconds
    bool showRestartText = true;
    
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
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    if (settingsScreen) {
                        // Handle "Back" button in settings screen
                        if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                            mouse_y > screenHeight/2 + 150 && mouse_y < screenHeight/2 + 182) {
                            Mix_PlayChannel(-1, fxSelect, 0);
                            settingsScreen = false;
                            gamePaused = true;
                        }
                    } else if (gamePaused) {
                        // Handle "Settings" button in pause screen
                        if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                            mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) {
                            Mix_PlayChannel(-1, fxSelect, 0);
                            settingsScreen = true;
                        }
                    }
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
                    else if (event.key.keysym.sym == SDLK_r && gameOver) {
                        Mix_PlayChannel(-1, fxSelect, 0);
                        gameOver = false;
                        resetGame();
                        gameStarted = true;
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
                    // toSettingsFromPause = false;
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
                    shield.setIsBorderAvailable(hasBorder);
                }

                // Handle back button
                else if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                         mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) 
                {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    settingsScreen = false;
                    // if (toSettingsFromPause == false) {
                    if (gamePaused == false) {
                        titleScreen = true;
                    } else {
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

            if (playDeathFX) {
                Mix_PlayChannel(-1, fxDeath, 0);
                playDeathFX = false;
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

            // If game over or pause, skip below code
            if (!gameOver && !gamePaused) {

                player.updatePosition();
                shield.updatePosition(player);
                threat.updatePosition();

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
    
                renderSprite(playerSprite, renderer, player.getX(), player.getY(), player.getWidth(), player.getHeight());
                renderSprite(shieldSprite, renderer, shield.getX(), shield.getY(), shield.getWidth(), shield.getHeight());
                renderSprite(lavaSprite, renderer, 0, lavaY, 800, 48);
                if (threat.getIsAvailable())
                    renderSprite(threatSprite, renderer, threat.getX(), threat.getY(), 32, 32);  

                renderSprite(scoreBoxSprite, renderer, 17, 17, 103, 70);
                Draw_Font(renderer, scoreManager.getScore().c_str(), 17 + (103 - 75)/2, 20, 75, 64, 64, {0, 0, 0});            
                
                Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), 17, 90, 74, 32, 32, {0, 0, 0});
                
                SDL_RenderPresent(renderer);
            }

            if (gamePaused) {
            // TODO: Display a pause screen
            // SDL_RenderClear(renderer);
                Mix_PauseMusic(); // Pause the music
                // Draw logo to fit the space between Freezed! and scoreManager.getHighScoreString()
                renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30 - 75, 400, 90);
                Draw_Font(renderer, "FREEZED!", screenWidth/2 - 35, screenHeight/2 - 150/2 - 125, 70, 32, 64, {213, 128, 90});
                Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), screenWidth/2 - 37, screenHeight/2 + 10 - 75, 74, 32, 32, {0, 0, 0});
                Draw_Font(renderer, "Press 'P' to continue", screenWidth/2 - 134, screenHeight/2 + 50 - 75, 268, 32, 32, {178, 150, 125});

                // Render settings button

                if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 100 - 75 && mouse_y < screenHeight/2 + 132 - 75)
                    Draw_Font(renderer, "Settings", screenWidth/2 - 30, screenHeight/2 + 100 - 75, 60, 32, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Settings", screenWidth/2 - 30, screenHeight/2 + 100 - 75, 60, 32, 32, {178, 150, 125});

                // Render restart button

                if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 150 - 75 && mouse_y < screenHeight/2 + 182 - 75)
                    Draw_Font(renderer, "Restart", screenWidth/2 - 30, screenHeight/2 + 150 - 75, 60, 32, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Restart", screenWidth/2 - 30, screenHeight/2 + 150 - 75, 60, 32, 32, {178, 150, 125});

                SDL_RenderPresent(renderer);

                if (mouse_pressed &&
                    mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 100 - 75 && mouse_y < screenHeight/2 + 132 - 75) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    //toSettingsFromPause = true;
                    settingsScreen = true;
                    gamePaused = false;
                    gameStarted = false;
                }

                if (mouse_pressed &&
                    mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 150 - 75 && mouse_y < screenHeight/2 + 182 - 75) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    gameRestarted = true;
                    gamePaused = false;
                    resetGame();
                    gameStarted = true;
                }
                continue;
            } else {
                // Resume the music
                Mix_ResumeMusic();
            }
        }

        // Game Over screen
        if (gameOver) {
            gameStarted = false;
            // Update flicker timer
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastToggleTime > flickerInterval) {
                showRestartText = !showRestartText;
                lastToggleTime = currentTime;
            }

            // Render the game over screen
            SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
            SDL_RenderClear(renderer);
            
            Draw_Font(renderer, "GAME OVER!", screenWidth/2 - 100, screenHeight/2 - 150, 200, 32, 64, {213, 128, 90});
            Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), screenWidth/2 - 37, screenHeight/2 - 100, 74, 32, 32, {0, 0, 0});

            if (showRestartText)
                Draw_Font(renderer, "Press 'R' to restart", screenWidth/2 - 134, screenHeight/2 - 50, 268, 32, 32, {178, 150, 125});
            
            if (mouse_x > screenWidth/2 - 70/2 && mouse_x < screenWidth/2 + 70/2 &&
                 mouse_y > screenHeight/2 && mouse_y < screenHeight/2 + 32)
                // Draw restart button with length 70 and center it
                Draw_Font(renderer, "Restart", screenWidth/2 - 70/2, screenHeight/2, 70, 32, 32, {0, 0, 0});
            else
                Draw_Font(renderer, "Restart", screenWidth/2 - 70/2, screenHeight/2, 70, 32, 32, {178, 150, 125});

            // Draw the home button
            if (mouse_x > screenWidth/2 - 70/2 && mouse_x < screenWidth/2 + 70/2 &&
                 mouse_y > screenHeight/2 + 50 && mouse_y < screenHeight/2 + 82)
                Draw_Font(renderer, "Home", screenWidth/2 - 70/2, screenHeight/2 + 50, 70, 32, 32, {0, 0, 0});
            else
                Draw_Font(renderer, "Home", screenWidth/2 - 70/2, screenHeight/2 + 50, 70, 32, 32, {178, 150, 125});
            
            SDL_RenderPresent(renderer);
            
            if (mouse_pressed &&
                 mouse_x > screenWidth/2 - 70/2 && mouse_x < screenWidth/2 + 70/2 &&
                 mouse_y > screenHeight/2 && mouse_y < screenHeight/2 + 32) {
                Mix_PlayChannel(-1, fxSelect, 0);
                resetGame();
                gameOver = false;
                gameStarted = true;
            }

            if (mouse_pressed &&
                 mouse_x > screenWidth/2 - 70/2 && mouse_x < screenWidth/2 + 70/2 &&
                 mouse_y > screenHeight/2 + 50 && mouse_y < screenHeight/2 + 82) {
                Mix_PlayChannel(-1, fxSelect, 0);
                gameOver = false;
                resetGame();
                titleScreen = true;
            }
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
    cleanupTexture(threatSprite);
    cleanupTexture(shieldSprite);

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
