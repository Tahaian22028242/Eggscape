#ifndef CLEANUP_HPP
#define CLEANUP_HPP

#include "resourcesPath.hpp"

// Function to clean up a texture
void cleanupTexture(SDL_Texture* texture);

// Function to clean up a sound effect
void cleanupSound(Mix_Chunk* sound);

// Function to clean up the system
void cleanupSystem();

#endif // CLEANUP_HPP