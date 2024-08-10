#ifndef RESOURCES_LOADER_HPP
#define RESOURCES_LOADER_HPP

#include "resourcesPath.hpp"

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
Mix_Chunk* loadSound(const char* filePath);
void renderSprite(SDL_Texture* sprite ,SDL_Renderer* renderer, int x, int y, int width, int height);
void Draw_Font(SDL_Renderer *renderer, const char *str, int x, int y, int width, int height, int size, SDL_Color color);

#endif // RESOURCES_LOADER_HPP