#include "header/platform.hpp"

Platform::Platform(int index) {
    width = platformWidth;
    height = platformHeight;
    
    x = rand() % 660 + 20;
    y = 0 - height - (index * 100);
    
    int coinInt = rand() % 4;
    
    if (coinInt == 0 || index == 0)
        hasCoin = false;
    else
        hasCoin = true;
    
    coinX = x + width/2 - 24/2;
    coinY = y - 24 - 5;
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

void Platform::updatePosition() {
    y+=1;

    if (y > screenHeight) {
        x = rand() % 660 + 20;
        y = 0 - height;
        
        int coinInt = rand() % 4;
        
        if (coinInt == 0)
            hasCoin = false;
        else
            hasCoin = true;
    }
 
    coinX = x + width/2 - 24/2;
    coinY = y - 24 - 5;    
}