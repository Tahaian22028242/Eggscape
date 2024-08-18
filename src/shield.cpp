#include "header/shield.hpp"

Shield::Shield() {
    int delay = 0;
    while (delay < 100) {
        delay++;
    }

    if (delay == 100) {
        width = shieldWidth;
        height = shieldHeight;
        moveType = rand() % 4;
        if (moveType != 3) { // standard move types
            x = rand() % (screenWidth - width);
            y = 0 - height;
        } else { // horizontal sine wave move type
            x = 0 - width;
            y = rand() % (screenHeight - height);
        }     
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

void Shield::setSineWaveParameters(float frequency, float amplitude, float phase) {
    sineWaveFrequency = frequency;
    sineWaveAmplitude = amplitude;
    sineWavePhase = phase;
}

void Shield::updatePosition(Player &player) {
    if (getIsOnPlayer()) {
        x = player.getX();
        y = player.getY();
    } 
    else {
        if (y > screenHeight) {
            y = 0 - height;
            x = rand() % (screenWidth - width);
            setMoveType(rand() % 4);
        }

        if (getMoveType() != 3) { // standard move types
            y += moveSpeed; 
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
        }
            
        else { // move sine wave cross the screen
            setSineWaveParameters(0.1, rand() % 10, 0);
            x += moveSpeed;
            y = sineWaveAmplitude * std::sin(sineWaveFrequency * x + sineWavePhase) + screenHeight / 2; // Center the sine wave vertically

            if (getIsBorderAvailable()) {
                if (x < 0) { // if there is a border, it will bounce off the wall
                    x = 0;
                    moveSpeed = -moveSpeed;
                    setMoveType(rand() % 4);
                }
                else if (x + width > screenWidth) { // if there is a border, it will bounce off the wall
                    x = screenWidth - width;
                    moveSpeed = -moveSpeed;
                    setMoveType(rand() % 4);
                }
            }
            else {
                if (x < 0) { // if there is no border, it will wrap around the screen
                    x = screenWidth - width;
                    setMoveType(rand() % 4);
                }
                else if (x + width > screenWidth) { // if there is no border, it will wrap around the screen
                    x = 0;
                    setMoveType(rand() % 4);
                }
            }
        }
    }
}

