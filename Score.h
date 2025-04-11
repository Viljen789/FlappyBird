#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <filesystem>
#include <vector>

class Score {
private:
    std::filesystem::path scoreFilePath;
    int currentScore;
    int currentTheme;
    static const int MAX_THEMES = 3;
    int highScores[MAX_THEMES];

    void loadHighScoresFromFile();
    void saveHighScoresToFile();

    std::vector<std::string> themeNames = {
        "Fugl",
        "Fisk",
        "Romvesen"
    };
    std::vector<std::string> formatedTopScores;

public:
    Score(const std::string& filePath = "score.txt");

    void resetCurrentScore();
    void incrementScore();
    void setTheme(int theme);

    int getCurrentScore() const;
    int getHighScore() const;
    bool isNewHighScore() const;

    void updateAndSaveHighScore();

    std::vector<std::string> getFormattedTopScores();
};

#endif // SCORE_H
