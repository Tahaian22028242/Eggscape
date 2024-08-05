#include "header/init.hpp"
#include <iostream>
using namespace std;

bool InitSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize: " << SDL_GetError() << std::endl;
        return false;
    }
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    
    *window = SDL_CreateWindow(
        "Terri-Fried",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenWidth, screenHeight,
        SDL_WINDOW_SHOWN
    );
    
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    
    SDL_Surface* egg = IMG_Load(playerImagePath);
    if (egg == nullptr) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return 1;
    }
    SDL_SetWindowIcon(*window, egg);
    SDL_FreeSurface(egg);
    
    return true;
}

bool InitAudio() {
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) < 0) {
<<<<<<< HEAD
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
=======
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
>>>>>>> origin/main
        return false;
    }
    // else SetMasterVolume(0.3f);
    return true;
}

bool InitTTF() {
    if (TTF_Init() == -1) {
<<<<<<< HEAD
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
=======
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
>>>>>>> origin/main
        return false;
    }
    return true;
}