#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "resourcesPath.hpp"

typedef struct {
    double x;
    double y;
} Vector2;

class Player {
private:
    double x;
    double y;
    int width;
    int height;
    bool onPlatform;
    Vector2 velocity;
    bool borderAvailable;
    int life;
    bool isAlive;
    bool isArmed;
    
public:
    Player(double x, double y/*, int width, int height*/);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getWidth();
    int getHeight();
    bool isOnPlatform();
    void setOnPlatform(bool result);
    void setVelocity(double x, double y);
    Vector2 getVelocity();
    void updatePosition();
    void setBorderAvailable(bool value);
    bool getBorderAvailable();
    void setLife(unsigned int value);
    unsigned int getLife();
    void setIsAlive(bool value);
    bool getIsAlive();
    void setIsArmed(bool value);
    bool getIsArmed();
};
#endif // PLAYER_HPP