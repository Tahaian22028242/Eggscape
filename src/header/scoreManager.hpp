#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include "resourcesPath.hpp"

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
#endif // SCORE_MANAGER_HPP
