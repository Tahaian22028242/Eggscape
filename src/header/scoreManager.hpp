#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
using namespace std;

class ScoreManager {
    private:
        int scoreInt;
        int highscoreInt;
        string score;
        string highscore;

    public:
        ScoreManager();
        
        void loadHighScore();
        void saveHighScore();
        void resetScore();
        void addScore(int amount);
        
        int getScoreInt();
        int getHighScoreInt();
        string getScore(); 
        string getHighScore();

};
#endif
