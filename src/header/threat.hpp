#ifndef THREAT_HPP
#define THREAT_HPP

#include "resourcesPath.hpp"

class Threat {
private:
    int x;
    int y;
    int width;
    int height;
    int riseSpeed;
    bool isAvailable;
    // bool isOnPlatform;
    // int velocityX;
    // int velocityY;
    // bool moveType; // 0 = not moving, 1 = moving
    //Platform& platform;

public:
    Threat(int startX, int startY);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setIsAvailable(bool value);
    bool getIsAvailable();
    // bool getHasCoin();
    // void setHasCoin(bool value);
    // int getCoinX();
    // int getCoinY();
    void updatePosition();
};
#endif // THREAT_HPP

