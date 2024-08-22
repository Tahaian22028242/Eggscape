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
    if (gameRestarted) {
        scoreManager.resetScore();
        player.setLife(playerMaxLife);
        gameRestarted = false;
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
    
    // Lava animation
    int lavaY = screenHeight - 32;
    double timer = 0; // Used to animate the lava.

    // Splash screen
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
    SDL_Texture* armedPlayerSprite = loadTexture(armedPlayerImagePath, renderer);
    SDL_Texture* killerPlayerSprite = loadTexture(killerPlayerImagePath, renderer);

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
    // Define the boundaries of the volume line
    int volumeLineMinX = screenWidth / 2 + 20;
    int volumeLineMaxX = screenWidth / 2 + 170;
    
    bool quit = false;
    bool titleScreen = true;
    bool gamePaused = false;
    bool gameStarted = false;
    bool settingsScreen = false;
    bool toSettingsFromPause = false;

    bool chooseSkinScreen = false;
    int skinChoice = 0; // Used to choose the skin of the player, default is 0.

    bool tutorialScreen = false;
    
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
            if (splashTimer < 100) { 
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
                
                renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30 - 100, 400, 90);
                Draw_Font(renderer, highscore, screenWidth/2 - 37, screenHeight/2 + 10 - 100, 80, 32, 32, {0, 0, 0});
                
                // Render start button
                SDL_Rect startButton = {screenWidth/2 - 25, screenHeight/2, 50, 32};
                if (mouse_x > startButton.x && mouse_x < startButton.x + startButton.w &&
                     mouse_y > startButton.y && mouse_y < startButton.y + startButton.h)
                    Draw_Font(renderer, "Start", startButton.x, startButton.y, startButton.w, startButton.h, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Start", startButton.x, startButton.y, startButton.w, startButton.h, 32, {178, 150, 125});

                // Render choose skin button
                SDL_Rect chooseSkinButton = {screenWidth/2 - 25, screenHeight/2 + 50, 50, 32};
                if (mouse_x > chooseSkinButton.x && mouse_x < chooseSkinButton.x + chooseSkinButton.w &&
                     mouse_y > chooseSkinButton.y && mouse_y < chooseSkinButton.y + chooseSkinButton.h)
                    Draw_Font(renderer, "Skins", chooseSkinButton.x, chooseSkinButton.y, chooseSkinButton.w, chooseSkinButton.h, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Skins", chooseSkinButton.x, chooseSkinButton.y, chooseSkinButton.w, chooseSkinButton.h, 32, {178, 150, 125});

                // Render tutorial button
                SDL_Rect tutorialButton = {screenWidth/2 - 40, screenHeight/2 + 100, 80, 32};
                if (mouse_x > tutorialButton.x && mouse_x < tutorialButton.x + tutorialButton.w &&
                     mouse_y > tutorialButton.y && mouse_y < tutorialButton.y + tutorialButton.h)
                    Draw_Font(renderer, "Tutorial", tutorialButton.x, tutorialButton.y, tutorialButton.w, tutorialButton.h, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Tutorial", tutorialButton.x, tutorialButton.y, tutorialButton.w, tutorialButton.h, 32, {178, 150, 125});

                // Render settings button
                SDL_Rect settingsButton = {screenWidth/2 - 40, screenHeight/2 + 150, 80, 32};
                if (mouse_x > settingsButton.x && mouse_x < settingsButton.x + settingsButton.w &&
                     mouse_y > settingsButton.y && mouse_y < settingsButton.y + settingsButton.h)
                    Draw_Font(renderer, "Settings", settingsButton.x, settingsButton.y, settingsButton.w, settingsButton.h, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Settings", settingsButton.x, settingsButton.y, settingsButton.w, settingsButton.h, 32, {178, 150, 125});
                
                SDL_RenderPresent(renderer);

                if (mouse_pressed &&
                     mouse_x > startButton.x && mouse_x < startButton.x + startButton.w &&
                     mouse_y > startButton.y && mouse_y < startButton.y + startButton.h) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    gameStarted = true;
                }

                if (mouse_pressed &&
                     mouse_x > settingsButton.x && mouse_x < settingsButton.x + settingsButton.w &&
                     mouse_y > settingsButton.y && mouse_y < settingsButton.y + settingsButton.h) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    settingsScreen = true;
                }

                if (mouse_pressed &&
                     mouse_x > chooseSkinButton.x && mouse_x < chooseSkinButton.x + chooseSkinButton.w &&
                     mouse_y > chooseSkinButton.y && mouse_y < chooseSkinButton.y + chooseSkinButton.h) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    chooseSkinScreen = true;
                }

                if (mouse_pressed &&
                     mouse_x > tutorialButton.x && mouse_x < tutorialButton.x + tutorialButton.w &&
                     mouse_y > tutorialButton.y && mouse_y < tutorialButton.y + tutorialButton.h) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    titleScreen = false;
                    tutorialScreen = true;
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
    
            if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                 mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132)
                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {213, 128, 90});
            else 
                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {178, 150, 125});
        
            // Draw volume lines
            SDL_SetRenderDrawColor(renderer, 178, 150, 125, 255);
            SDL_RenderDrawLine(renderer, volumeLineMinX, screenHeight/2 - 82, volumeLineMaxX, screenHeight/2 - 82);
            SDL_RenderDrawLine(renderer, volumeLineMinX, screenHeight/2 - 32, volumeLineMaxX, screenHeight/2 - 32);
        
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
                    if (toSettingsFromPause) // If the player goes to the settings screen from the pause screen, then return to the pause screen.
                        gameStarted = true; // Return to the game, then check if the game is paused.
                    else // If the player goes to the settings screen from the title screen, then return to the title screen.
                        titleScreen = true;
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

            // Make the music rect movement only within the boundaries of the current volume bar
            if (draggingMusic) {
                int new_x = std::min(std::max(mouse_x, volumeLineMinX), volumeLineMaxX); // Clamp the new x position
                musicVolume = (new_x - (screenWidth/2 - 50)) * MIX_MAX_VOLUME / 200; // Calculate the new volume
                Mix_VolumeMusic(musicVolume);
            }

            // Make the sound rect movement only within the boundaries of the current volume bar
            if (draggingSound) {
                int new_x = std::min(std::max(mouse_x, volumeLineMinX), volumeLineMaxX);
                soundVolume = (new_x - (screenWidth/2 - 50)) * MIX_MAX_VOLUME / 200;
                Mix_Volume(-1, soundVolume); // Set volume for all channels
            }
        }

        if (chooseSkinScreen) {
            SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
            SDL_RenderClear(renderer);
        
            // Draw labels
            Draw_Font(renderer, "CHOOSE SKIN", screenWidth/2 - 70, screenHeight/2 - 200, 140, 32, 64, {213, 128, 90});

            // Draw the player's skin image side by side at the center of the screen, then draw the rectangle around them with colored border if the mouse is hovering over them.
            // Draw the rectangles at the center of the screen
            SDL_Rect rect0 = {screenWidth/2 - 120, screenHeight/2 - 100, 32, 32};
            renderSprite(playerSprite, renderer, rect0.x, rect0.y, rect0.w, rect0.h);
            SDL_Rect rect1 = {screenWidth/2 - 20, screenHeight/2 - 100, 34, 34};
            renderSprite(armedPlayerSprite, renderer, rect1.x, rect1.y, rect1.w, rect1.h);
            SDL_Rect rect2 = {screenWidth/2 + 80, screenHeight/2 - 100, 34, 34};
            renderSprite(killerPlayerSprite, renderer, rect2.x, rect2.y, rect2.w, rect2.h);
            
            SDL_SetRenderDrawColor(renderer, 213, 128, 90, 255); // Set the color to orange to draw the rectangle around the player's skin image. 
            // Draw the rectangle around the player's skin image if the mouse is hovering over them.
            if (skinChoice == 0 || 
                (mouse_x > rect0.x && mouse_x < rect0.x + 32 &&
                 mouse_y > rect0.y && mouse_y < rect0.y + 32)) {
                SDL_RenderDrawRect(renderer, &rect0);
                Draw_Font(renderer, "Default", rect0.x - 16, rect0.y + 60, 64, 32, 32, {213, 128, 90});
            } else if (skinChoice == 1 || 
                        (mouse_x > rect1.x && mouse_x < rect1.x + 34 &&
                         mouse_y > rect1.y && mouse_y < rect1.y + 34)) {
                SDL_RenderDrawRect(renderer, &rect1);
                Draw_Font(renderer, "Armed", rect1.x - 16, rect1.y + 60, 64, 32, 32, {213, 128, 90});
            } else if (skinChoice == 2 ||
                        (mouse_x > rect2.x && mouse_x < rect2.x + 34 &&
                         mouse_y > rect2.y && mouse_y < rect2.y + 34)) {
                SDL_RenderDrawRect(renderer, &rect2);
                Draw_Font(renderer, "Killer", rect2.x - 15, rect2.y + 60, 64, 32, 32, {213, 128, 90});
            }

            // Draw the back button
            if (mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132)
                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {213, 128, 90});
            else
                Draw_Font(renderer, "Back", screenWidth/2 - 20, screenHeight/2 + 100, 40, 32, 32, {178, 150, 125});

            SDL_RenderPresent(renderer);

            // Handle skin choosing
            if (mouse_down && mouse_x > rect0.x && mouse_x < rect0.x + rect0.w &&
                mouse_y > rect0.y && mouse_y < rect0.y + rect0.h) {
                Mix_PlayChannel(-1, fxSelect, 0);
                skinChoice = 0;
            } else if (mouse_down && mouse_x > rect1.x && mouse_x < rect1.x + rect1.w &&
                       mouse_y > rect1.y && mouse_y < rect1.y + rect1.h) {
                Mix_PlayChannel(-1, fxSelect, 0);
                skinChoice = 1;
            } else if (mouse_down && mouse_x > rect2.x && mouse_x < rect2.x + rect2.w &&
                       mouse_y > rect2.y && mouse_y < rect2.y + rect2.h) {
                Mix_PlayChannel(-1, fxSelect, 0);
                skinChoice = 2;
            }

            // Handle back button
            if (mouse_pressed && mouse_x > screenWidth/2 - 20 && mouse_x < screenWidth/2 + 20 &&
                mouse_y > screenHeight/2 + 100 && mouse_y < screenHeight/2 + 132) {
                Mix_PlayChannel(-1, fxSelect, 0);
                chooseSkinScreen = false;
                titleScreen = true;
            }
        }

        // TODO: Implement the tutorial screen
        if (tutorialScreen) {
            SDL_SetRenderDrawColor(renderer, 0.933 * 255, 0.894 * 255, 0.882 * 255, 1.0 * 255);
            SDL_RenderClear(renderer);
        
            // Draw labels
            Draw_Font(renderer, "TUTORIAL", screenWidth/2 - 50, screenHeight/2 - 200, 100, 32, 64, {213, 128, 90});
            Draw_Font(renderer, "1. Click and drag the egg to set the direction and power of the jump.", 50, screenHeight/2 - 150, 70*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "2. Collect coins to increase your score.", 50, screenHeight/2 - 110, 41*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "3. Avoid the threats and the lava.", 50, screenHeight/2 - 70, 35*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "4. Get the shield to protect the egg from the threats.", 50, screenHeight/2 - 30, 55*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "5. The game ends when the egg falls into the lava or the life reaches 0.", 50, screenHeight/2 + 10, 73*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "6. Press 'B' to toggle the border.", 50, screenHeight/2 + 50, 35*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "7. Press 'P' to pause the game.", 50, screenHeight/2 + 90, 32*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "8. Press 'R' to restart the game when the game is over.", 50, screenHeight/2 + 130, 56*10, 32, 32, {0, 0, 0});
            Draw_Font(renderer, "9. Press 'ESC' to quit the game.", 50, screenHeight/2 + 170, 33*10, 32, 32, {0, 0, 0});

            // Draw the back button
            SDL_Rect backButton = {screenWidth/2 + 300, screenHeight/2 + 180, 40, 32};
            if (mouse_x > backButton.x && mouse_x < backButton.x + backButton.w &&
                mouse_y > backButton.y && mouse_y < backButton.y + backButton.h)
                Draw_Font(renderer, "Back", backButton.x, backButton.y, backButton.w, backButton.h, 32, {213, 128, 90});
            else
                Draw_Font(renderer, "Back", backButton.x, backButton.y, backButton.w, backButton.h, 32, {178, 150, 125});

            SDL_RenderPresent(renderer);

            // Handle back button
            if (mouse_pressed && mouse_x > backButton.x && mouse_x < backButton.x + backButton.w &&
                mouse_y > backButton.y && mouse_y < backButton.y + backButton.h) {
                Mix_PlayChannel(-1, fxSelect, 0);
                tutorialScreen = false;
                titleScreen = true;
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
    
                if (skinChoice == 0) {
                    renderSprite(playerSprite, renderer, player.getX(), player.getY(), player.getWidth(), player.getHeight());
                } else if (skinChoice == 1) {
                    renderSprite(armedPlayerSprite, renderer, player.getX(), player.getY(), player.getWidth(), player.getHeight());
                } else if (skinChoice == 2) {
                    renderSprite(killerPlayerSprite, renderer, player.getX(), player.getY(), player.getWidth(), player.getHeight());
                }
                renderSprite(shieldSprite, renderer, shield.getX(), shield.getY(), shield.getWidth(), shield.getHeight());
                renderSprite(lavaSprite, renderer, 0, lavaY, 800, 48);
                if (threat.getIsAvailable())
                    renderSprite(threatSprite, renderer, threat.getX(), threat.getY(), 32, 32);  

                renderSprite(scoreBoxSprite, renderer, 17, 17, 103, 70);
                Draw_Font(renderer, scoreManager.getScore().c_str(), 17 + (103 - 75)/2, 20, 75, 64, 64, {0, 0, 0});            
                
                Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), 17, 90, 80, 32, 32, {0, 0, 0});
                // Draw the life bar under the high score
                Draw_Font(renderer, "LIFE: ", 17, 120, 60, 32, 32, {0, 0, 0});
                Draw_Font(renderer, to_string(player.getLife()).c_str(), 17 + 60, 120, 16, 32, 32, {0, 0, 0});
                // for (int i = 0; i < player.getLife(); i++) {
                //     renderSprite(shieldSprite, renderer, 17 + i * 32, 120, 32, 32);
                // }

                SDL_RenderPresent(renderer);
            }

            if (toSettingsFromPause) { // If the player goes to the settings screen from the pause screen, then the game is paused.
                toSettingsFromPause = false;
                gamePaused = true;
            }

            // TODO: Display a pause screen
            if (gamePaused) {
                Mix_PauseMusic(); // Pause the music
                // Draw logo to fit the space between Freezed! and scoreManager.getHighScoreString()
                renderSprite(logo, renderer, screenWidth/2 - 200, screenHeight/2 - 45 - 30 - 75, 400, 90);
                Draw_Font(renderer, "FREEZED!", screenWidth/2 - 35, screenHeight/2 - 150/2 - 125, 70, 32, 64, {213, 128, 90});
                Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), screenWidth/2 - 37, screenHeight/2 + 10 - 75, 80, 32, 32, {0, 0, 0});
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

                // Draw the home button
                if (mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 200 - 75 && mouse_y < screenHeight/2 + 232 - 75)
                    Draw_Font(renderer, "Home", screenWidth/2 - 30, screenHeight/2 + 200 - 75, 60, 32, 32, {0, 0, 0});
                else
                    Draw_Font(renderer, "Home", screenWidth/2 - 30, screenHeight/2 + 200 - 75, 60, 32, 32, {178, 150, 125});

                SDL_RenderPresent(renderer);

                if (mouse_pressed &&
                    mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 100 - 75 && mouse_y < screenHeight/2 + 132 - 75) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    gamePaused = false;
                    gameStarted = false;
                    toSettingsFromPause = true;
                    settingsScreen = true;
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

                if (mouse_pressed &&
                    mouse_x > screenWidth/2 - 30 && mouse_x < screenWidth/2 + 30 &&
                    mouse_y > screenHeight/2 + 200 - 75 && mouse_y < screenHeight/2 + 232 - 75) {
                    Mix_PlayChannel(-1, fxSelect, 0);
                    gamePaused = false;
                    gameStarted = false;
                    titleScreen = true;
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
            
            Draw_Font(renderer, "YOU HAVE BEEN COOKED!", screenWidth/2 - 200, screenHeight/2 - 150, 20*20, 32, 64, {213, 128, 90});
            Draw_Font(renderer, scoreManager.getHighScoreString().c_str(), screenWidth/2 - 37, screenHeight/2 - 100, 80, 32, 32, {0, 0, 0});

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
                gameRestarted = true;
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
    cleanupTexture(armedPlayerSprite);
    cleanupTexture(killerPlayerSprite);
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
