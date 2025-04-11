#include "Bird.h"
#include "Game.h"
#include "AnimationWindow.h"


Bird::Bird(TDT4102::AnimationWindow &gameWindow) : window(gameWindow),
                                                   xPosition{0},
                                                   yPosition{0},
                                                   gravity{0},
                                                   isDead{false},
                                                   spaceWasPressed{false},
                                                   currentTheme{0},
                                                   currentBackground{0},
                                                   currentSprite{0} {
    xPosition = window.width() / 2;
    yPosition = 0;
    updatePosition();

    positionHistory.clear();
    XOffsets.clear();
    generateRandomIntervals();
}


void Bird::generateRandomIntervals() {
    ///Lager random verdier for når trailene skal oppdateres
    std::uniform_int_distribution<int> trailDist(
        static_cast<int>(trailUpdateInterval * 0.6),
        static_cast<int>(trailUpdateInterval * 1.4)
    );

    currentTrailInterval = trailDist(rng);
}

void Bird::reset() {
    /// Resetter variablene til fuglen når man starter ett nytt spill
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
    XOffsets.clear();
    frameCounter = 0;

    generateRandomIntervals();

    updatePosition();
}

int Bird::getTheme() const {
    return currentTheme;
}

void Bird::setTheme(int theme) {
    ///Oppdaterer variablene til temaet
    currentTheme = theme % static_cast<int>(backgrounds.size());
    currentBackground = currentTheme;
    background = backgrounds[static_cast<size_t>(currentBackground)];

    if (currentTheme == 0) {
        currentSprite = 0;
    } else if (currentTheme == 1) {
        currentSprite = 1;
    } else {
        currentSprite = 2;
    }
    sprite = sprites[static_cast<size_t>(currentSprite)];

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
            if (i < XOffsets.size()) {
                xOffset = static_cast<int>(XOffsets[i]);
            }
            int trailSize = BIRD_WIDTH - static_cast<int>(i * 3);
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
    /// Ulik tyngdekraft for forskjellige temaer
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
    /// Lager trails fra spritesene, og oppdaterer dem, ved å lagre verdiene før i en vector, og oppdatere dem med ny x og (og y for fisken) slik at de flytter seg bakover
    if (frameCounter >= currentTrailInterval) {
        frameCounter = 0;
        positionHistory.insert(positionHistory.begin(), position);
        XOffsets.insert(XOffsets.begin(), 0.0);

        if (currentTheme != 1 && positionHistory.size() > TRAIL_LENGTH) {
            positionHistory.pop_back();
            if (XOffsets.size() > TRAIL_LENGTH) {
                XOffsets.pop_back();
            }
        }

        generateRandomIntervals();
    }

    for (int i = 0; i < XOffsets.size(); i++) {
        double speed = (currentTheme == 1) ? trailSpeed : trailSpeed * 0.5;
        XOffsets[i] += speed;

        if (i < positionHistory.size() && XOffsets[i] > window.width()) {
            if (i == XOffsets.size() - 1) {
                XOffsets.pop_back();
                if (i < positionHistory.size()) {
                    positionHistory.erase(positionHistory.begin() + i);
                }
            }
        }
    }

    while (positionHistory.size() > XOffsets.size()) {
        positionHistory.pop_back();
    }
    while (XOffsets.size() > positionHistory.size()) {
        XOffsets.pop_back();
    }
}

void Bird::jump() {
    if (isDead)
        return;
    /// Ulik hopplogikk for forskjellige temaer
    bool spaceIsPressed = window.is_key_down(KeyboardKey::SPACE);
    spaceJustPressed = spaceIsPressed && !spaceWasPressed;
    ///Må bruke en "smart" måte for å passe på at man bare holder inne på space på fiske-levelen.
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

/// bare returnerer verdier
int Bird::returnXPos() const {
    return xPosition;
}

int Bird::returnYPos() const {
    return yPosition;
}

bool Bird::dying() const {
    return isDead;
}
