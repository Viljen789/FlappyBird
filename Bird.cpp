#include "Bird.h"
#include "Game.h"
#include "AnimationWindow.h"


Bird::Bird(TDT4102::AnimationWindow &gameWindow) : window(gameWindow),
                                                   xPosition{0},
                                                   yPosition{0},
                                                   gravity{0},
                                                   currentTheme{0},
                                                   currentBackground{0},
                                                   currentSprite{0},
                                                   isDead{false},
                                                   spaceWasPressed{false} {
    xPosition = window.width() / 2;
    yPosition = 0;
    updatePosition();

    positionHistory.clear();
    bubbleXOffsets.clear();
    generateRandomIntervals();
}

void Bird::generateRandomIntervals() {
    std::uniform_int_distribution<int> trailDist(
        static_cast<int>(trailUpdateInterval * 0.6),
        static_cast<int>(trailUpdateInterval * 1.4)
    );
    
    std::uniform_int_distribution<int> bubbleDist(
        static_cast<int>(bubbleSpawnInterval * 0.6),
        static_cast<int>(bubbleSpawnInterval * 1.4)
    );
    
    currentTrailInterval = trailDist(rng);
    currentBubbleInterval = bubbleDist(rng);
}

void Bird::reset() {
    xPosition = window.width() / 2;
    yPosition = BIRD_HEIGHT;
    isDead = false;
    spaceWasPressed = false;
    spaceJustPressed = false;

    setTheme(currentTheme);

    if (currentTheme == 0 || currentTheme == 1) {
        gravity = window.height() / 150.0;
    } else {
        gravity = window.height() / 150.0;
        currentSprite = 2;
        sprite = sprites[currentSprite];
    }

    positionHistory.clear();
    bubbleXOffsets.clear();
    frameCounter = 0;
    bubbleFrameCounter = 0;

    generateRandomIntervals();

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
        currentSprite = 2;
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

        for (size_t i = 0; i < positionHistory.size(); ++i) {
            int xOffset = 0;
            if (i < bubbleXOffsets.size()) {
                xOffset = static_cast<int>(bubbleXOffsets[i]);
            }
            int trailSize = BIRD_WIDTH - (i * 3);
            if (trailSize < 10) trailSize = 10;

            if (currentTheme == 0) {
                window.draw_image({positionHistory[i].x - xOffset, positionHistory[i].y}, trails[0], trailSize,
                                  trailSize);
            } else if (currentTheme == 1) {
                if (positionHistory[i].x - xOffset >= 0) {
                    window.draw_image({
                                          positionHistory[i].x - xOffset,
                                          positionHistory[i].y - static_cast<int>(xOffset * 1.5)
                                      }, trails[1], trailSize, trailSize);
                }
            } else {
                if (trailSize >= BIRD_WIDTH * 0.3) {
                    window.draw_image({positionHistory[i].x - xOffset, positionHistory[i].y}, trails[2], trailSize,
                                    trailSize);
                }
            }
        }
    }
}

void Bird::renderBackground() {
    window.draw_image({0, 0}, background, window.width(), window.height());
}

void Bird::update() {
    if (isDead)
        return;
    yPosition += gravity;

    if (currentTheme == 0) {
        gravity += 0.3;
    } else if (currentTheme == 1) {
        gravity = 3;
    } else if (currentTheme == 2) {
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

    frameCounter++;
    bubbleFrameCounter++;

    if (frameCounter >= currentTrailInterval) {
        frameCounter = 0;
        positionHistory.insert(positionHistory.begin(), position);
        bubbleXOffsets.insert(bubbleXOffsets.begin(), 0.0);

        if (currentTheme != 1 && positionHistory.size() > TRAIL_LENGTH) {
            positionHistory.pop_back();
            if (bubbleXOffsets.size() > TRAIL_LENGTH) {
                bubbleXOffsets.pop_back();
            }
        }

        generateRandomIntervals();
    }
    
    for (size_t i = 0; i < bubbleXOffsets.size(); i++) {
        double speed = (currentTheme == 1) ? bubbleSpeed : bubbleSpeed * 0.5;
        bubbleXOffsets[i] += speed;

        if (i < positionHistory.size() && bubbleXOffsets[i] > window.width()) {
            if (i == bubbleXOffsets.size() - 1) {
                bubbleXOffsets.pop_back();
                if (i < positionHistory.size()) {
                    positionHistory.erase(positionHistory.begin() + i);
                }
            }
        }
    }

    while (positionHistory.size() > bubbleXOffsets.size()) {
        positionHistory.pop_back();
    }
    while (bubbleXOffsets.size() > positionHistory.size()) {
        bubbleXOffsets.pop_back();
    }
}

void Bird::jump() {
    if (isDead)
        return;

    bool spaceIsPressed = window.is_key_down(KeyboardKey::SPACE);
    spaceJustPressed = spaceIsPressed && !spaceWasPressed;
    if (currentTheme == 1 and spaceIsPressed) {
        gravity = -gravity;
    }
    if (spaceJustPressed) {
        if (currentTheme == 0) {
            gravity = jumpHeight;
        } else if (currentTheme == 2) {
            gravity = -gravity;
            currentSprite = (currentSprite == 2) ? 3 : 2;
            sprite = sprites[currentSprite];
        }
    }

    spaceWasPressed = spaceIsPressed;
}

int Bird::returnXPos() const {
    return xPosition;
}
int Bird::returnYPos() const {
    return yPosition;
}

bool Bird::dying() const {
    return isDead;
}


