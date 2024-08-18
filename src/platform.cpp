#include "header/platform.hpp"

Platform::Platform(int index) {
    width = platformWidth;
    height = platformHeight;
    
    x = rand() % 660 + 20;
    y = 0 - height - (index * 100);

    int coinInt = rand() % 4;
    moveType = rand() % 4;

    if (index == 0) {
        moveType = 0;
        coinInt = 0;
    }
    
    if (coinInt == 0)
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

int Platform::getIsMoving() {
    return moveType;
}

void Platform::updatePosition() {
    y += platformSpeed;

    if (moveType != 0) {
        if (moveType == 1) {
            x -= platformSpeed;
            if (x < 0) {
                x = 0;
                moveType = 2;
            }
        } else if (moveType == 2) {
            x += platformSpeed;
            if (x + width > screenWidth) {
                x = screenWidth - width;
                moveType = 1;
            }
        }

        else {
            bool isLeft = rand() % 2;
            if (isLeft) {
                x -= platformSpeed;
                isLeft = false;
            } else {
                x += platformSpeed;
                isLeft = true;
            }
        }
    }

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
