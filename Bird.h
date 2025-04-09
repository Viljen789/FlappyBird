#ifndef BIRD_H
#define BIRD_H

#include "AnimationWindow.h"
#include "Image.h"
#include "Point.h"
#include <vector>
#include <string>

constexpr int BIRD_WIDTH = 50;
constexpr int BIRD_HEIGHT = 50;

class Bird
{
public:
    Bird(TDT4102::AnimationWindow &gameWindow);

    void setTheme(int theme);

    void reset();

    void render();

    void renderBackground();

    void update();

    void jump();

    bool dying() const;

    TDT4102::Point getPosition() const { return position; }
    int getWidth() const { return BIRD_WIDTH; }
    int getHeight() const { return BIRD_HEIGHT; }


private:
    void updatePosition();

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

    TDT4102::AnimationWindow &window;

    TDT4102::Image sprite;
    TDT4102::Image background;

    TDT4102::Point position;
    int xPosition;
    double yPosition;
    double gravity;
    double jumpHeight = -6.0;
    bool isDead;
    bool spaceWasPressed;

    int currentTheme;
    int currentBackground;
    int currentSprite;
    bool spaceJustPressed = false;
};

#endif // BIRD_H
