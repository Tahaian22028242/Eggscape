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
    int moveType; // 0 = normal, 1 = sine wave
    float sineWaveFrequency;
    float sineWaveAmplitude;
    float sineWavePhase;

public:
    Threat(int startX, int startY);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setIsAvailable(bool value);
    bool getIsAvailable();
    void setMoveType(int type);
    int getMoveType();
    void setSineWaveParameters(float frequency, float amplitude, float phase);
    void updatePosition();
};
#endif // THREAT_HPP

