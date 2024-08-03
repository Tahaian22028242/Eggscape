#ifndef PLATFORM_H
#define PLATFORM_H

#include "resourcesPath.hpp"

class Platform {
private:
    double x;
    double y;
    int width;
    int height;
    bool hasCoin;
    int coinX;
    int coinY;
    
public:
    Platform(int index);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool getHasCoin();
    void setHasCoin(bool value);
    int getCoinX();
    int getCoinY();
    void updatePosition();
};
#endif