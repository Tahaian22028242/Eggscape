#ifndef INIT_HPP
#define INIT_HPP

#include "resourcesPath.hpp"

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer);
bool InitAudio();
bool InitTTF();

#endif // INIT_HPP