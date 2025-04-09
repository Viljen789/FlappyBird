#include "Bird.h"
#include "Game.h"
#include "AnimationWindow.h"
#include <algorithm>

constexpr int ALIEN_SPRITE_NORMAL = 2;
constexpr int ALIEN_SPRITE_FLIPPED = 3;

Bird::Bird(TDT4102::AnimationWindow &gameWindow) : window(gameWindow),
                                                   xPosition{0},
                                                   yPosition{0},
                                                   gravity{0},
                                                   currentTheme{0},
                                                   currentBackground{0},
                                                   currentSprite{0},
                                                   isDead{false},
                                                   spaceWasPressed{false} {
    xPosition = window.width() / 3;
    yPosition = window.height() / 2;
    updatePosition();
}

void Bird::reset() {
    xPosition = window.width() / 3;
    yPosition = window.height() / 2;
    isDead = false;
    spaceWasPressed = false;

    setTheme(currentTheme);

    if (currentTheme == 0 || currentTheme == 1) {
        gravity = window.height() / 150.0;
    } else {
        gravity = window.height() / 150.0;
        currentSprite = ALIEN_SPRITE_NORMAL;
        sprite = sprites[currentSprite];
    }

    updatePosition();
}

void Bird::setTheme(int theme) {
    currentTheme = theme % backgrounds.size();
    currentBackground = currentTheme;
    background = backgrounds[currentBackground];

    if (currentTheme == 0) {
        currentSprite = 0;
    } else if (currentTheme == 1) {
        currentSprite = 1;
    } else {
        currentSprite = ALIEN_SPRITE_NORMAL;
    }
    sprite = sprites[currentSprite];

    updatePosition();
}

void Bird::updatePosition() {
    position = {xPosition, static_cast<int>(yPosition)};
}

void Bird::render() {
    if (!isDead) {
        window.draw_image(position, sprite, BIRD_WIDTH, BIRD_HEIGHT);
    }
}

void Bird::renderBackground() {
    window.draw_image({0, 0}, background, window.width(), window.height());
}

void Bird::update() {
    if (isDead)
        return;
    yPosition += gravity;

    if (currentTheme == 0 || currentTheme == 1) {
        gravity += 0.3;
    } else {
        double acceleration = 0.3;
        double maxGravitySpeed = 8.0;

        if (gravity >= 0) {
            gravity += acceleration;
            gravity = std::min(gravity, maxGravitySpeed);
        } else {
            gravity -= acceleration;
            gravity = std::max(gravity, -maxGravitySpeed);
        }
    }

    if (yPosition <= 0 || (yPosition + BIRD_HEIGHT) >= window.height()) {
        isDead = true;
    }

    updatePosition();
}

void Bird::jump() {
    if (isDead)
        return;

    bool spaceIsPressed = window.is_key_down(KeyboardKey::SPACE);
    spaceJustPressed = spaceIsPressed && !spaceWasPressed;

    if (spaceJustPressed) {
        if (currentTheme == 0) {
            gravity = jumpHeight;
        } else if (currentTheme == 1) {
            gravity = jumpHeight * 1.2;
        } else {
            gravity = -gravity;

            currentSprite = (currentSprite == 2) ? 3 : 2;
            sprite = sprites[currentSprite];
        }
    }

    spaceWasPressed = spaceIsPressed;
}

bool Bird::dying() const {
    return isDead;
}

