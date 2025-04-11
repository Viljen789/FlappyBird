#include "Game.h"

#include <iostream>
#include <string>
#include <widgets/Button.h>
#include <stdexcept>

Game::Game(int width, int height) : window(width, height, "Flappy Bird"),
                                    bird(window),
                                    score("./score.txt")
// score("../score.txt")
{
    gameOver = true;
    scoreHasBeenSaved = false;

    try
    {
        bird.setTheme(currentTheme);
        score.setTheme(currentTheme);
        initButtons();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during game initialization: " << e.what() << std::endl;
    }
}

void Game::initButtons()
{
    int buttonWidth = 150;
    int buttonHeight = 50;
    int buttonSpacing = 100;
    int totalWidth = (buttonWidth * 3) + (buttonSpacing * 2);
    int startX = (window.width() - totalWidth) / 2;
    int buttonY = (window.height() - 50);

    themeButtons.push_back(TDT4102::Button({startX, buttonY},
                                           buttonWidth, buttonHeight, "Fugl"));

    themeButtons.push_back(TDT4102::Button({startX + (buttonWidth + buttonSpacing), buttonY},
                                           buttonWidth, buttonHeight, "Fisk"));

    themeButtons.push_back(TDT4102::Button({startX + (buttonWidth + buttonSpacing) * 2, buttonY},
                                           buttonWidth, buttonHeight, "Romvesen"));

    themeButtons[0].setCallback(std::bind(&Game::birdThemeCallback, this));
    themeButtons[1].setCallback(std::bind(&Game::fishThemeCallback, this));
    themeButtons[2].setCallback(std::bind(&Game::alienThemeCallback, this));
    for (auto &button : themeButtons)
    {
        window.add(button);
    }
}

// Theme button callbacks
void Game::birdThemeCallback()
{
    handleThemeSelection(0);
}

void Game::fishThemeCallback()
{
    handleThemeSelection(1);
}

void Game::alienThemeCallback()
{
    handleThemeSelection(2);
}

// Reset game state
void Game::reset()
{
    try
    {
        bird.reset();

        towers.clear();
        towers.reserve(36);
        Tower t2 = Tower{window, window.width()};
        towers.push_back(t2);

        current_time = time(0);

        gameOver = false;
        scoreHasBeenSaved = false;
        score.resetCurrentScore();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred while resetting game: " << e.what() << std::endl;
        gameOver = true;
        towers.clear();
    }
}

// Gameflow
void Game::run()
{
    while (!window.should_close())
    {
        processInput();
        update();
        render();
        window.next_frame();
    }
}

void Game::processInput()
{
    bird.jump();
}

void Game::handleThemeSelection(int themeIndex)
{
    try
    {
        bird.setTheme(themeIndex);
        score.setTheme(themeIndex);
        currentTheme = themeIndex;

        if (gameOver)
        {
            reset();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred while changing theme: " << e.what() << std::endl;
        std::cerr << "Theme change failed. Staying with current theme." << std::endl;
    }
}

// Update game state
void Game::update()
{
    if (!gameOver)
    {
        bird.update();
        score.incrementScore();

        // tower.updatePosition();
        int i = 0;
        for (auto &t : towers)
        {
            t.updatePosition();
            /*if(t.isOutOfScreen()) {
                towers.erase(towers.begin(), towers.begin() + i);
            }
            i++;*/
        }

        if (time(0) == current_time + 3)
        {
            current_time = static_cast<int>(time(0));
            towers.push_back(Tower{window, window.width()});
            std::cout << towers.size() << std::endl;
        }

        // Colision detection
        for (int i = 0; i < int(towers.size()); i++)
        {
            if (towers[static_cast<size_t>(i)].checkCollision(bird.returnXPos(), bird.returnYPos()))
            {
                gameOver = true;
            };
        }

        if (bird.dying())
        {
            gameOver = true;
        }
    }
}

std::string Game::formatCurrentScore() const
{
    return "Score: " + std::to_string(score.getCurrentScore());
}

void Game::render()
{
    bird.renderBackground();
    bird.render();

    // TOWER LOGIC
    for (auto &t : towers)
    {
        t.render();
    }

    if (!gameOver)
    {
        window.drawScore(score.getCurrentScore(), {10, 10}, white);
    }
    else
    {
        window.draw_image({0, 0}, waitingScreen, window.width(), window.height());
        window.draw_text({10, 10}, formatCurrentScore(),
                         (!bird.getTheme() ? black : white),
                         fontSize);

        window.draw_text({220, window.height() / 3 * 2}, "Hvilken modus vil du spille?",
                         white, fontSize, font);

        score.loadHighScoresFromFile();

        // Highscores and other text
        const std::vector<std::string> topScores = score.getFormattedTopScores();
        window.draw_text({0, 100}, topScores[0],
                         black, fontSize, font);
        window.draw_text({300, 100}, topScores[1],
                         white, fontSize, font);
        window.draw_text({550, 100}, topScores[2],
                         white, fontSize, font);
        window.draw_text({0, 500}, "Trykk for å hoppe",
                         white, fontSize, font);
        window.draw_text({250, 500}, "Hold inne for å flyte",
                         white, fontSize, font);
        window.draw_text({520, 500}, "Trykk for å skifte retning",
                         white, fontSize, font);

        // Check for new highscore
        if (score.isNewHighScore())
        {
            if (!scoreHasBeenSaved)
            {
                score.updateAndSaveHighScore();
                scoreHasBeenSaved = true;
            }
            TDT4102::Point centerPos = {window.width() / 2 - 150, window.height() / 2 - 50};
            window.draw_text(centerPos, newHighscore, success, fontSize, font);
        }

        // Keyboard controls as for testing
        if (window.is_key_down(KeyboardKey::KEY_1))
        {
            handleThemeSelection(0);
        }
        else if (window.is_key_down(KeyboardKey::KEY_2))
        {
            handleThemeSelection(1);
        }
        else if (window.is_key_down(KeyboardKey::KEY_3))
        {
            handleThemeSelection(2);
        }
    }
}
