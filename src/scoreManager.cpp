#include "header/scoreManager.hpp"

ScoreManager::ScoreManager() : scoreInt(0), highscoreInt(loadHighScore()) {
    score = "000";
    highscore = "BEST: " + std::to_string(highscoreInt);
}

int ScoreManager::loadHighScore() {
    std::ifstream scorefile("highscore.bin", std::ios::binary);
    if (!scorefile) {
        cout << "Error: Could not load high score" << endl;
        return 0;
    }
    int ret;
    scorefile.read(reinterpret_cast<char*>(&ret), sizeof(int));
    if (scorefile.gcount() != sizeof(int)) {
        cout << "Oh no: Could not load high score" << endl;
        return 0;
    }
    return ret;
}

void ScoreManager::saveHighScore() const {
    std::ofstream scorefile("highscore.bin", std::ios::binary);
    if (!scorefile) {
        cout << "Error: Could not save high score" << endl;
        return;
    }
    scorefile.write(reinterpret_cast<const char*>(&highscoreInt), sizeof(int));
}

int ScoreManager::getHighScore() const {
    return highscoreInt;
}

void ScoreManager::addScore(int amount) {
    scoreInt += amount;

    std::ostringstream scoreStream;
    scoreStream << std::setw(3) << std::setfill('0') << scoreInt;
    score = scoreStream.str();

    if (scoreInt > highscoreInt) {
        highscoreInt = scoreInt;
        highscore = "BEST: " + std::to_string(highscoreInt);
    }
}

void ScoreManager::resetScore() {
    scoreInt = 0;
    score = "000";
    saveHighScore();
}

std::string ScoreManager::getScore() const {
    return score;
}

std::string ScoreManager::getHighScoreString() const {
    return highscore;
}