#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "AnimationWindow.h"
#include <string>

class GameWindow : public TDT4102::AnimationWindow {
public:
    GameWindow(int width, int height, const std::string &title);

    void drawScore(int score, TDT4102::Point position, TDT4102::Color color);
};

#endif // GAMEWINDOW_H
