#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "init.hpp"

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
Mix_Chunk* LoadSound(const char* filePath);
void Draw_Font(SDL_Renderer *renderer, const char *str, int x, int y, int width, int height, int size, SDL_Color color);

#endif // TEXTURE_LOADER_H