#ifndef RESOURCES_PATH_HPP
#define RESOURCES_PATH_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;     

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "init.hpp"
#include "resourcesLoader.hpp"
#include "player.hpp"
#include "platform.hpp"
#include "scoreManager.hpp"
#include "cleanup.hpp"

const int screenWidth = 800;
const int screenHeight = 450;

const double pi = 3.1415926535897;
const int gravity = 1;

// Set the default width and height of the platform
const int platformWidth = 100;
const int platformHeight = 32;

// All the paths to the images
extern const char* playerImagePath;
extern const char* lavaImagePath;
extern const char* platformImagePath;
extern const char* coinImagePath;
extern const char* scoreBoxImagePath;
extern const char* logoImagePath;
extern const char* splashEggImagePath;

// All the paths to the sound effects
extern const char* fxLaunchPath;
extern const char* fxClickPath;
extern const char* fxDeathPath;
extern const char* fxCoinPath;
extern const char* fxSplashPath;
extern const char* fxSelectPath;

// All the paths to the font
extern const char* fontPath;

#endif // GENERAL_VALUE_H