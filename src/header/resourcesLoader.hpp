#ifndef RESOURCES_LOADER_HPP
#define RESOURCES_LOADER_HPP

#include "resourcesPath.hpp"

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
Mix_Chunk* LoadSound(const char* filePath);
void Draw_Font(SDL_Renderer *renderer, const char *str, int x, int y, int width, int height, int size, SDL_Color color);

#endif // RESOURCES_LOADER_HPP