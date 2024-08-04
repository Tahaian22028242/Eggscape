#ifndef INIT_HPP
#define INIT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "resourcesPath.hpp"

bool InitSDL(SDL_Window** window, SDL_Renderer** renderer);
bool InitAudio();
bool InitTTF();

#endif // INIT_HPP