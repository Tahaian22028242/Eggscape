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
    int moveType;
    int moveSpeed;
    bool isOnPlayer;
    bool isBorderAvailable;
    float sineWaveFrequency;
    float sineWaveAmplitude;
    float sineWavePhase;
    
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
    void setSineWaveParameters(float frequency, float amplitude, float phase);
    void updatePosition(Player &player);
};
#endif // SHIELD_HPP