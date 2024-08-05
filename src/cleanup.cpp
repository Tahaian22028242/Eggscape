#include "header/cleanup.hpp"
#include <iostream>
using namespace std;

void cleanupTexture(SDL_Texture* texture) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    } else {
        cerr << "Attempted to clean up a null texture." << endl;
    }
}

void cleanupSound(Mix_Chunk* sound) {
    if (sound != nullptr) {
        Mix_FreeChunk(sound);
    } else {
        cerr << "Attempted to clean up a null sound." << endl;
    }
}

void cleanupSystem() {
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}