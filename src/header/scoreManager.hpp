// #ifndef SCORE_MANAGER_HPP
// #define SCORE_MANAGER_HPP

// #include "resourcesPath.hpp"

// class ScoreManager {
//     private:
//         int scoreInt;
//         int highscoreInt;
//         string score;
//         string highscore;

//     public:
//         ScoreManager();
        
//         void loadHighScore();
//         void saveHighScore();
//         void resetScore();
//         void addScore(int amount);
        
//         int getScoreInt();
//         int getHighScoreInt();
//         string getScore(); 
//         string getHighScore();

// };
// #endif // SCORE_MANAGER_HPP

#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include "resourcesPath.hpp"

class ScoreManager {
public:
    ScoreManager();
    int getHighScore() const;
    void addScore(int amount);
    void resetScore();
    void saveHighScore() const;
    std::string getScore() const;
    std::string getHighScoreString() const;

private:
    int scoreInt;
    int highscoreInt;
    std::string score;
    std::string highscore;

    int loadHighScore();
};

#endif // SCOREMANAGER_HPP
