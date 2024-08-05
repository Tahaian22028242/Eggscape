#ifndef CLEANUP_H
#define CLEANUP_H

#include "init.hpp"

// Function to clean up a texture
void cleanupTexture(SDL_Texture* texture);

// Function to clean up a sound effect
void cleanupSound(Mix_Chunk* sound);

void cleanupSystem();

#endif // RESOURCE_CLEANUP_H