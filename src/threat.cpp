#include "header/threat.hpp"

Threat::Threat() {
    int delay = 0;
    while (delay < 100) {
        delay++;
    }

    if (delay == 100) {
        x = rand() % (screenWidth - threatWidth);
        y = screenHeight;
        width = threatWidth;
        height = threatHeight;
        riseSpeed = rand() % (maxVelocity - minVelocity) + minVelocity;
        moveType = rand() % 2;
        isAvailable = true;
    }
}

int Threat::getX() {
    return x;
}

int Threat::getY() {
    return y;
}

int Threat::setX(int value) {
    x = value;
}

int Threat::setY(int value) {
    y = value;
}

int Threat::getWidth() {
    return width;
}

int Threat::getHeight() {
    return height;
}

void Threat::setIsAvailable(bool value) {
    isAvailable = value;
}

bool Threat::getIsAvailable() {
    return isAvailable;
}

void Threat::setMoveType(int type) {
    moveType = type;
}

int Threat::getMoveType() {
    return moveType;
}

void Threat::setSineWaveParameters(float frequency, float amplitude, float phase) {
    sineWaveFrequency = frequency;
    sineWaveAmplitude = amplitude;
    sineWavePhase = phase;
}

void Threat::updatePosition() {
    if (getIsAvailable() == false) {
        return;
    }
    
    if (moveType == 0) { // normal movement
        y -= riseSpeed;
    } else if (moveType == 1) { // sine wave movement
        y -= riseSpeed;
        setSineWaveParameters(0.1, rand() % 10, 0);
        x = x + sineWaveAmplitude * sin(sineWaveFrequency * y + sineWavePhase);
    }

    if (y < 0 - height) {
        x = rand() % (screenWidth - width);
        y = screenHeight;
        riseSpeed = rand() % (maxVelocity - minVelocity) + minVelocity;
        moveType = rand() % 2;
    }
}
    

