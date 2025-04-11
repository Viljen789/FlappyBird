#include "Game.h"

#include <iostream>
#include <string>

Game::Game(int width, int height): window(width, height),
                                   bird(window),
                                   score("../score.txt") {
    gameOver = true;
    scoreHasBeenSaved = false;

    bird.setTheme(currentTheme);
    score.setTheme(currentTheme);
                                   bird(window) {
    reset();
}

int current_time = 0;

void Game::reset() {
    bird.reset();

    towers.clear();
    //Tower t = Tower{window, 0};
    towers.reserve(36);
    Tower t2 = Tower {window, window.width()};
    towers.push_back(t2);
    //towers.push_back(t2);
    current_time = time(0);
 
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
    bird.jump();
}

void Game::handleThemeSelection(int themeIndex) {
    bird.setTheme(themeIndex);
    score.setTheme(themeIndex);

    if (gameOver) {
        reset();
    }
}

void Game::update() {
    if (!gameOver) {
        bird.update();
        score.incrementScore();

        if (bird.dying()) {
            gameOver = true;
        }
    }
}

std::string Game::formatCurrentScore() const {
    return "Score: " + std::to_string(score.getCurrentScore());
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
    bird.renderBackground();

    bird.render();

    // TOWER LOGIC
    for (auto& t : towers) {
        t.render();
    }
    //here

    if (!gameOver) {
        window.draw_text({10, 10}, formatCurrentScore(), black, fontSize);
    } else {
        window.draw_image({0, 0}, waitingScreen, window.width(), window.height());
        window.draw_text({10, 10}, formatCurrentScore(), (!bird.getTheme()?black:white), fontSize);

        window.draw_text({220, window.height() / 3}, "Hvilken modus vil du spille?", white, fontSize, font);
        window.draw_text({0, 100}, score.getFormattedTopScores()[0], black, fontSize, font);
        window.draw_text({350, 100}, score.getFormattedTopScores()[1], white, fontSize, font);
        window.draw_text({700, 100}, score.getFormattedTopScores()[2], white, fontSize, font);

        if (score.isNewHighScore() && !scoreHasBeenSaved) {
            window.draw_text({textLocation.x, textLocation.y + 100}, newHighscore, success,
                             fontSize, font);
            score.updateAndSaveHighScore();
            scoreHasBeenSaved = true;
        }


        window.draw_text({100, window.height() / 3 * 2}, "Trykk 1", black, 20, font);
        window.draw_text({420, window.height() / 3 * 2}, "Trykk 2", white, 20, font);
        window.draw_text({750, window.height() / 3 * 2}, "Trykk 3", white, 20, font);
        if (window.is_key_down(KeyboardKey::KEY_1)) {
            handleThemeSelection(0);
        } else if (window.is_key_down(KeyboardKey::KEY_2)) {
            handleThemeSelection(2);
        } else if (window.is_key_down(KeyboardKey::KEY_3)) {
            handleThemeSelection(1);
        }
    }
}
    std::string scoreText = "Score: " + std::to_string(score);
    std::string highScore = "Highscore: " + std::to_string(score);
    window.draw_text({10, 10}, scoreText, TDT4102::Color::black, 20, TDT4102::Font::courier_bold_italic);
}

void Game::update() {

    bird.update();

    //tower.updatePosition();
    int i = 0;
    for (auto& t : towers) {
        t.updatePosition();
        /*if(t.isOutOfScreen()) {
            towers.erase(towers.begin(), towers.begin() + i);
        }
        i++;*/
    }
    if (time(0) == current_time + 3) {
        current_time = time(0);
        towers.push_back(Tower{window, window.width()});
        std::cout << towers.size() << std::endl;
    }
    

    //kollisjonslogikk
    for (int i = 0; i < int(towers.size()); i++) {
        if(towers[i].checkCollision(bird.returnXPos(), bird.returnYPos())) {
            gameOver = true;
        };
    }

    if (bird.dying()) {
        gameOver = true;
    }

    score++;
}


void Game::spawnObstacle() {
    // Vegard fikse
}

void Game::reset() {
    gameOver = false;
    scoreHasBeenSaved = false;

    bird.reset();
    score.resetCurrentScore();
}
