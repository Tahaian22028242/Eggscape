#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "resourcesPath.hpp"

class Platform {
private:
    int x;
    int y;
    int width;
    int height;
    bool hasCoin;
    int coinX;
    int coinY;
    int isMoving; // 0 = not moving, 1 = moving
    
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
#endif // PLATFORM_HPP