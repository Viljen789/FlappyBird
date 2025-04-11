#ifndef BIRD_H
#define BIRD_H

#include "AnimationWindow.h"
#include "Image.h"
#include "Point.h"
#include <vector>
#include <random>

constexpr int BIRD_WIDTH = 50;
constexpr int BIRD_HEIGHT = 50;
constexpr int TRAIL_LENGTH = 100;
constexpr int TRAIL_SPACING = 100;
constexpr int TRAIL_OFFSET = 50;

class Bird {
public:
    Bird(TDT4102::AnimationWindow &gameWindow);

    void setTheme(int theme);

    int getTheme() const;

    void reset();

    void render();

    void renderBackground();

    void trail();

    void update();

    void jump();

    bool dying() const;

    int returnXPos() const;

    int returnYPos() const;

    TDT4102::Point getPosition() const { return position; }

private:
    void updatePosition();

    void generateRandomIntervals();

    //The path may differ based on system, use the one that works
    // std::vector<TDT4102::Image> sprites = {
    //     TDT4102::Image("./assets/BirdSprite.png"),
    //     TDT4102::Image("./assets/FishSprite.png"),
    //     TDT4102::Image("./assets/AlienSprite.png"),
    //     TDT4102::Image("./assets/AlienSpriteFlipped.png")
    // };
    // std::vector<TDT4102::Image> backgrounds = {
    //     TDT4102::Image("./assets/BirdBackground.png"),
    //     TDT4102::Image("./assets/FishBackground.png"),
    //     TDT4102::Image("./assets/AlienBackground.png")
    // };std::vector<TDT4102::Image> trails = {
    //     TDT4102::Image("./assets/BirdTrail.png"),
    //     TDT4102::Image("./assets/FishTrail.png"),
    //     TDT4102::Image("./assets/AlienTrail.png")
    // };
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
    std::vector<TDT4102::Image> trails = {
        TDT4102::Image("../assets/BirdTrail.png"),
        TDT4102::Image("../assets/FishTrail.png"),
        TDT4102::Image("../assets/AlienTrail.png")
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

    std::vector<TDT4102::Point> positionHistory;
    int frameCounter = 0;
    int trailUpdateInterval = 100;
    int currentTrailInterval;

    std::mt19937 rng{std::random_device{}()};

    std::vector<double> XOffsets;
    double trailSpeed = 2.0;
};

#endif // BIRD_H
