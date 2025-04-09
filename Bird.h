//
// Created by vilje on 09/04/2025.
//

#ifndef BIRD_H
#define BIRD_H
#include <vector>
#include <widgets/Button.h>

#include "animationwindow.h"


class Bird{
public:
    Bird(TDT4102::AnimationWindow &gameWindow);

    void setTheme(int theme);

    void reset();

    void render();

    void renderBackground();

    void update();

    void updatePosition();

    void jump();

    bool dying() const;


private:
    std::vector<TDT4102::Image> sprites = {
        TDT4102::Image("../assets/BirdSprite.png"),
        TDT4102::Image("../assets/FishSprite.png"),
        TDT4102::Image("../assets/AlienSprite.png"),
        TDT4102::Image("../assets/AlienSpriteFlipped.png")
    };
    std::vector<TDT4102::Image> backgrounds = {
        TDT4102::Image("../assets/BirdBackground.png"),
        TDT4102::Image("../assets/FishBackground.png"),
        TDT4102::Image("../assets/AlienBackground.png")
    };
    std::vector<std::pair<int, float> > fallInfo = {
        {1.01, window.height() / 100},
        {1.02, window.height() / 100},
        {1.03, window.height() / 100}
    };
    TDT4102::Image sprite;
    TDT4102::Image background;
    TDT4102::Point position;
    TDT4102::AnimationWindow &window;
    double jumpHeight = -10.0;
    int xPosition;
    double yPosition;
    double gravity;
    int currentTheme;
    int currentBackground;
    int currentSprite;
    int currentPosition{};
    int currentWindow{};
    int currentXPosition{};
    int currentYPosition{};
    bool isDead = false;
    static constexpr int BIRD_WIDTH = 50;
    static constexpr int BIRD_HEIGHT = 50;
    bool spaceWasPressed = false;
};


#endif //BIRD_H
