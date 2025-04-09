#include "Game.h"

#include <iostream>
#include <string>
#include <widgets/Button.h>

Game::Game(int width, int height): window(width, height),
                                   bird(window) {
    reset();
}


void Game::reset() {
    bird.reset();
    gameOver = false;
    score = 0;
}

void Game::run() {
    while (!window.should_close()) {
        processInput();
        update();
        render();
        window.next_frame();
    }
}

void Game::processInput() {
    bird.jump(); // Always call jump to properly track space key state
    
    if (gameOver && window.is_key_down(KeyboardKey::ENTER)) {
        reset();
    }

    if (window.is_key_down(KeyboardKey::KEY_1)) {
        bird.setTheme(0);
    } else if (window.is_key_down(KeyboardKey::KEY_2)) {
        bird.setTheme(1);
    } else if (window.is_key_down(KeyboardKey::KEY_3)) {
        bird.setTheme(2);
    }
}


void Game::render() {
    if (gameOver) {
        window.draw_text(textLocation, fail, textColor, fontSize, font);
        // Kan kanskje bruke dette seinare idk
        // TDT4102::Button birdButton{birdLocation, 100, 50, "Bird"};
        // TDT4102::Button fishButton{fishLocation, 100, 50, "Fish"};
        // TDT4102::Button alienButton{alienLocation, 100, 50, "Alien"};
        //
        // birdButton.setCallback([this]() { this->birdButtonCallback(); });
        // fishButton.setCallback([this]() { this->fishButtonCallback(); });
        // alienButton.setCallback([this]() { this->alienButtonCallback(); });
        //
        // static bool buttonsInitialized = false;
        // if (!buttonsInitialized) {
        //     birdButton.setCallback([this]() { this->birdButtonCallback(); });
        //     fishButton.setCallback([this]() { this->fishButtonCallback(); });
        //     alienButton.setCallback([this]() { this->alienButtonCallback(); });
        //
        //     window.add(birdButton);
        //     window.add(fishButton);
        //     window.add(alienButton);
        //     buttonsInitialized = true;
        // }
        return;
    }

    bird.renderBackground();
    bird.render();

    std::string scoreText = "Score: " + std::to_string(score);
    std::string highScore = "Highscore: " + std::to_string(score);
    window.draw_text({10, 10}, scoreText, TDT4102::Color::black, 20, TDT4102::Font::courier_bold_italic);
}

void Game::update() {
    if (gameOver) return;

    bird.update();


    //kollisjonslogikk

    if (bird.dying()) {
        gameOver = true;
    }

    score++;
}


void Game::spawnObstacle() {
    //Vegard fikse
}

