#include "header/shield.hpp"

Shield::Shield() {
    int delay = 0;
    while (delay < 100) {
        delay++;
    }

    if (delay == 100) {
        width = shieldWidth;
        height = shieldHeight;
        x = rand() % (screenWidth - shieldWidth);
        y = 0 - height;
        moveType = rand() % 4;
        moveSpeed = rand() % (maxVelocity - minVelocity) + minVelocity;
        isOnPlayer = false;
    }
}

int Shield::getX() {
    return x;
}

int Shield::getY() {
    return y;
}

int Shield::getWidth() {
    return width;
}

int Shield::getHeight() {
    return height;
}

bool Shield::getIsOnPlayer() {
    return isOnPlayer;
}

void Shield::setIsOnPlayer(bool value) {
    isOnPlayer = value;
}

int Shield::getMoveType() {
    return moveType;
}

void Shield::setMoveType(int value) {
    moveType = value;
}

bool Shield::getIsBorderAvailable() {
    return isBorderAvailable;
}

void Shield::setIsBorderAvailable(bool value) {
    isBorderAvailable = value;
}

void Shield::updatePosition(Player &player) {
    if (getIsOnPlayer()) {
        x = player.getX();
        y = player.getY();
    } 
    else {
        y += moveSpeed;
        if (y > screenHeight) {
            // if (getIsBorderAvailable()) { // it will bounce up and down if there is a border
            //     y = screenHeight - height;
            //     moveSpeed = -moveSpeed;
            // }
            //else { // it will wrap around the screen if there is no border
                y = 0 - height;
                x = rand() % (screenWidth - width);
            //}
            setMoveType(rand() % 4);
        }

        if (getMoveType() != 0) { // special move types
            if (getMoveType() == 1) { // move left
                x -= moveSpeed;
                if (getIsBorderAvailable()) {
                    if (x < 0) { // if there is a border, it will bounce off the wall
                        x = 0;
                        moveType = 2;
                    }
                    else { // if there is no border, it will wrap around the screen
                        x = screenWidth - width;
                    }
                }
            } 
            else if (getMoveType() == 2) { // move right
                x += moveSpeed;
                if (getIsBorderAvailable()) {
                    if (x + width > screenWidth) { // if there is a border, it will bounce off the wall
                        x = screenWidth - width;
                        moveType = 1;
                    }
                    else { // if there is no border, it will wrap around the screen
                        x = 0;
                    }
                }
            } 
            else { // move randomly
                bool isLeft = rand() % 2;
                if (isLeft) {
                    x -= moveSpeed;
                    if (getIsBorderAvailable()) {
                        if (x < 0) { // if there is a border, it will bounce off the wall
                            x = 0;
                            moveType = 2;
                        }
                        else { // if there is no border, it will wrap around the screen
                            x = screenWidth - width;
                        }
                    }
                } 
                else {
                    x += moveSpeed;
                    if (getIsBorderAvailable()) {
                        if (x + width > screenWidth) { // if there is a border, it will bounce off the wall
                            x = screenWidth - width;
                            moveType = 1;
                        }
                        else { // if there is no border, it will wrap around the screen
                            x = 0;
                        }
                    }
                }
            }
        }
    }
}

