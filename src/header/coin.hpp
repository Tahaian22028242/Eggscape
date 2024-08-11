#ifndef COIN_HPP
#define COIN_HPP

#include "resourcesPath.hpp"
#include "platform.hpp"

class Platform; // Forward declaration

class Coin {
private:
    int x;
    int y;
    int width;
    int height;
    bool isAvailable;
    // bool isOnPlatform;
    // int velocityX;
    // int velocityY;
    // bool moveType; // 0 = not moving, 1 = moving
    //Platform& platform;

public:
    Coin(int index, Platform& platform);
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
#endif // COIN_HPP

