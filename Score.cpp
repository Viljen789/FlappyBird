#include "Score.h"
#include <iostream>
#include <fstream>
#include <limits>

Score::Score(const std::string& filePath) : scoreFilePath(filePath), currentScore(0), currentTheme(0) {
    for (int i = 0; i < MAX_THEMES; ++i) {
        highScores[i] = 0;
    }
    loadHighScoresFromFile();
}

void Score::resetCurrentScore() {
    currentScore = 0;
}

void Score::incrementScore() {
    currentScore++;
}

void Score::setTheme(int theme) {
    if (theme >= 0 && theme < MAX_THEMES) {
        currentTheme = theme;
    } else {
        std::cerr << "Warning: Invalid theme index " << theme << ". Using theme 0." << std::endl;
        currentTheme = 0;
    }
}

int Score::getCurrentScore() const {
    return currentScore;
}

int Score::getHighScore() const {
    return highScores[currentTheme];
}

bool Score::isNewHighScore() const {
    return currentScore > highScores[currentTheme];
}

void Score::updateAndSaveHighScore() {
    if (isNewHighScore()) {
        highScores[currentTheme] = currentScore;
        saveHighScoresToFile();
    }
}

void Score::loadHighScoresFromFile() {
    std::ifstream inputStream(scoreFilePath);

    if (!inputStream) {
        std::cerr << "Info: Score file not found at " << scoreFilePath.string() << ". Creating new file with default scores." << std::endl;
        saveHighScoresToFile();
        return;
    }

    int theme = 0;
    int score = 0;
    while (inputStream >> theme >> score) {
        if (theme >= 0 && theme < MAX_THEMES) {
            if (score > highScores[theme]) {
                 highScores[theme] = score;
            }
        } else {
            std::cerr << "Invalid theme index " << theme << " found in score file. Skipping line." << std::endl;
        }
    }
    if (inputStream.bad()) {
         std::cerr << "Error reading score file: " << scoreFilePath.string() << std::endl;
    }
    inputStream.clear();
}

void Score::saveHighScoresToFile() {
    std::ofstream outputStream(scoreFilePath, std::ios::trunc);

    if (!outputStream) {
        std::cerr << "Could not open score file for writing at: " << scoreFilePath.string() << std::endl;
        return;
    }

    for (int i = 0; i < MAX_THEMES; ++i) {
        outputStream << i << " " << highScores[i] << "\n";
    }

    if (outputStream.fail()) {
         std::cerr << "Error writing to score file: " << scoreFilePath.string() << std::endl;
    }
}

std::vector<std::string> Score::getFormattedTopScores() {

    for (int i = 0; i < MAX_THEMES; ++i) {
        formatedTopScores.push_back("Rekord " + themeNames[i] + ": " + std::to_string(highScores[i]));
    }
    return formatedTopScores;
}
