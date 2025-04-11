#ifndef TOWER_H
#define TOWER_H

#include "AnimationWindow.h"
#include "Image.h"
#include "Point.h"

constexpr int TOWER_WIDTH = 50;
constexpr int SPEED = 1;
constexpr int SPACE_INBETWEEN = 150;

class Tower {
private:
    TDT4102::AnimationWindow &window;

    TDT4102::Image spriteup;
    TDT4102::Image spritedown;

    int height_upper;
    int height_lower;

    TDT4102::Point position_lower;
    TDT4102::Point position_upper;

    int space_between;
    int yPosition_upper;
    int yPosition_lower;
    int xPosition;
    bool outOfScreen;

public:
    Tower(TDT4102::AnimationWindow &gameWindow, int xPosition);

    void updatePosition();

    void render();

    bool checkCollision(int birdX, int birdY) const;

    bool isOutOfScreen() const;
};

#endif
