#include "GameWindow.h"
#include <string>

GameWindow::GameWindow(int width, int height, const std::string &title)
    : TDT4102::AnimationWindow(0, 0, width, height, title) {
}

void GameWindow::drawScore(int score, TDT4102::Point position, TDT4102::Color color) {
    /// skriven inn den live scoren, og viser den på skjermen.
    std::string scoreText = "Score: " + std::to_string(score);
    draw_text(position, scoreText, color);
}
