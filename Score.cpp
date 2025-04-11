#include "Score.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>

Score::Score(const std::string &filePath) : scoreFilePath(filePath), currentScore(0), currentTheme(0) {
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
    return currentScore >= highScores[currentTheme];
}

void Score::updateAndSaveHighScore() {
    if (isNewHighScore()) {
        highScores[currentTheme] = currentScore;
        saveHighScoresToFile();
    }
}

void Score::loadHighScoresFromFile() {
    try {
        std::ifstream inputFile(scoreFilePath);
        if (!inputFile.is_open()) {
            std::cerr << "Warning: Could not open score file. Using default scores." << std::endl;
            return;
        }

        int theme, score;
        while (inputFile >> theme >> score) {
            if (theme >= 0 && theme < MAX_THEMES) {
                highScores[theme] = score;
            }
        }

        inputFile.close();
    } catch (const std::exception &e) {
        std::cerr << "Error loading scores: " << e.what() << std::endl;
    }
}

void Score::saveHighScoresToFile() {
    try {
        std::ofstream outputFile(scoreFilePath);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Could not open score file for writing." << std::endl;
            return;
        }

        for (int i = 0; i < MAX_THEMES; ++i) {
            outputFile << i << " " << highScores[i] << std::endl;
        }

        outputFile.close();
    } catch (const std::exception &e) {
        std::cerr << "Error saving scores: " << e.what() << std::endl;
    }
}

//formatting the highscores
std::vector<std::string> Score::getFormattedTopScores() {
    formatedTopScores.clear();

    for (int i = 0; i < MAX_THEMES; ++i) {
        std::string scoreText = themeNames[i] + ": " + std::to_string(highScores[i]);
        formatedTopScores.push_back(scoreText);
    }

    return formatedTopScores;
}
