#ifndef SHIELD_HPP
#define SHIELD_HPP

#include "resourcesPath.hpp"

class Player;

class Shield {
private:
    int x;
    int y;
    int width;
    int height;
    int moveType; // 0 = not moving, 1 = moving
    int moveSpeed;
    bool isOnPlayer;
    bool isBorderAvailable;
    
public:
    Shield();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool getIsOnPlayer();
    void setIsOnPlayer(bool value);
    bool getIsBorderAvailable();
    void setIsBorderAvailable(bool value);
    int getMoveType();
    void setMoveType(int value);
    void updatePosition(Player &player);
};
#endif // SHIELD_HPP