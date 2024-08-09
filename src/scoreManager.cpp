#include "header/scoreManager.hpp"

ScoreManager::ScoreManager() {
    resetScore();
    highscoreInt = loadHighScore();
    highscore = "BEST: " + to_string(highscoreInt);
}

void ScoreManager::loadHighScore() {
    ifstream scorefile("highscore.txt");
    if (scorefile.is_open()) {
        scorefile >> highscoreInt;
        scorefile.close();
    }
}

void ScoreManager::saveHighScore() {
    ofstream scorefile("highscore.txt");
    scorefile << highscoreInt;
    scorefile.close();
}

void ScoreManager::addScore(int amount) {
    scoreInt += amount;
    
    if (scoreInt < 10)
        score = "00" + to_string(scoreInt);
    else if (scoreInt < 100)
        score = "0" + to_string(scoreInt);
    else
        score = to_string(scoreInt);
    
    if (scoreInt > highscoreInt) {
        highscoreInt = scoreInt;
        highscore = "BEST: " + to_string(highscoreInt);
    }
}

void ScoreManager::resetScore() {
    scoreInt = 0;
    score = "00" + to_string(scoreInt);
    saveHighScore();
}

int ScoreManager::getScoreInt() {
    return scoreInt;
}

int ScoreManager::getHighScoreInt() {
    return highscoreInt;
}

string ScoreManager::getScore() {
    return score;
}

string ScoreManager::getHighScore() {
    return highscore;
}
