#include "Tower.h"
#include "Game.h"
#include "AnimationWindow.h"
#include <iostream>
#include <cstdlib>
#include <random>

Tower::Tower(TDT4102::AnimationWindow &gameWindow, int xPos) : window(gameWindow), xPosition(window.width()) {
    srand(time(0));
    //xPosition = xPos;
    yPosition_upper = 0;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(200, window.height()-200);

    height_upper = distr(gen);
    yPosition_lower = yPosition_upper + height_upper + SPACE_INBETWEEN;
    height_lower = window.height() - yPosition_lower;

    spriteup = TDT4102::Image("./assets/tower_up.png");
    spritedown = TDT4102::Image("./assets/tower_down.png");
}

void Tower::updatePosition() {
    //position_upper = {xPosition - SPEED, yPosition};
}

void Tower::render() {
    xPosition -= SPEED;
    position_upper = {xPosition, yPosition_upper};
    position_lower = {xPosition, yPosition_lower};

    window.draw_image(position_upper, spritedown, TOWER_WIDTH, height_upper);
    window.draw_image(position_lower, spriteup, TOWER_WIDTH, height_lower);
}

bool Tower::checkCollision (int birdX, int birdY) {
    if (birdX > xPosition - TOWER_WIDTH/2 && birdX < xPosition + TOWER_WIDTH/2) {
        if(birdY < height_upper || birdY > yPosition_lower) {
            return true;
        }
    }
    return false;
}