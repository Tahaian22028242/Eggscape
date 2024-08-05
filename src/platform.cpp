#include "header/platform.hpp"
<<<<<<< HEAD
#include <cmath>
=======
<<<<<<< HEAD

#include <cmath>
=======
#include <cmath>

>>>>>>> 645291966eb5004e0fa2512a38d41fb6aa59bcbd
>>>>>>> origin/main

Platform::Platform(int index) {
    
    // Set the x and y position of the platform
    x = rand() % 660 + 20; // 660 is the width of the screen, 20 is the offset
    y = 0 - height - (index * 100); // 100 is the distance between each platform
    
<<<<<<< HEAD
    int coinInt = rand() % 4; // 1 in 5 chance of having a coin
=======
<<<<<<< HEAD
    int coinInt = rand() % 4; // 1 in 5 chance of having a coin
=======
    int coinInt = rand() % 5; // 1 in 5 chance of having a coin
>>>>>>> 645291966eb5004e0fa2512a38d41fb6aa59bcbd
>>>>>>> origin/main
    
    if (coinInt == 0 || index == 0) // First platform will never have a coin
        hasCoin = false;
    else
        hasCoin = true;
    
    coinX = x + width/2 - 24/2; // 24 is the width of the coin
    coinY = y - 24 - 5; // 5 is the offset
}

int Platform::getX() {
    return x;
}

int Platform::getY() {
    return y;
}

int Platform::getWidth() {
    return width;
}

int Platform::getHeight() {
    return height;
}

bool Platform::getHasCoin() {
    return hasCoin;
}

void Platform::setHasCoin(bool value) {
    hasCoin = value;
}

int Platform::getCoinX() {
    return coinX;
}

int Platform::getCoinY() {
    return coinY;
}

void Platform::updatePosition() { // Move the platform down the screen
    y+=1;
    
    coinX = x + width/2 - 24/2;
    coinY = y - 24 - 5;
    
    if (y > screenHeight) {
        x = rand() % 660 + 20;
        y = 0 - height;
        
        int coinInt = rand() % 4;
        
        if (coinInt == 0)
            hasCoin = false;
        else
            hasCoin = true;
    }
}