#include "Bird.h"
#include "Game.h"
#include "AnimationWindow.h"

Bird::Bird(TDT4102::AnimationWindow &gameWindow) : window(gameWindow), xPosition{0},
                                                   yPosition{0},
                                                   gravity{0},
                                                   currentTheme{0},
                                                   currentBackground{0},
                                                   currentSprite{0} {
}


void Bird::reset() {
    xPosition = window.width() / 2;
    yPosition = window.height() / 2;
    gravity = window.height() / 100;
    setTheme(currentTheme);
    isDead = false;
}

void Bird::setTheme(int theme) {
    currentTheme = theme % sprites.size();
    currentSprite = currentTheme;
    currentBackground = currentTheme;

    sprite = sprites[currentSprite];
    background = backgrounds[currentBackground];
    updatePosition();
}

void Bird::updatePosition() {
    position = {xPosition, static_cast<int>(yPosition)};
}

void Bird::render() {
    window.draw_image(position, sprite, BIRD_WIDTH, BIRD_HEIGHT);
}

void Bird::renderBackground() {
    window.draw_image({0, 0}, background, window.width(), window.height());
}

void Bird::update() {
    if (isDead) return;
    if (currentTheme == 0) {
        yPosition += gravity;
        gravity += 0.5;
        gravity = std::max(gravity, 1.0);
    } else {
        yPosition += gravity;
    }

    if (yPosition <= 0 || yPosition >= window.height()) {
        isDead = true;
    }

    updatePosition();
}


void Bird::jump() {
    if (isDead) return;
    bool spaceIsPressed = window.is_key_down(KeyboardKey::SPACE);

    if (currentTheme == 0) {
        yPosition -= window.height() / 50;
        gravity = jumpHeight;
    } else if (currentTheme == 1) {
        yPosition -= gravity*2;
        gravity = -jumpHeight;
    } else{

        if (spaceIsPressed && !spaceWasPressed) {
            if (currentSprite == 2) {
                currentSprite = 3;
                gravity = -gravity;
            } else if (currentSprite == 3) {
                currentSprite = 2;
                gravity = -gravity;
            }
            sprite = sprites[currentSprite];
        }
    }
    spaceWasPressed = spaceIsPressed;
    updatePosition();
}

    bool Bird::dying() const {
        return isDead;
    }
