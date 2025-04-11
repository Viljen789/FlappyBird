#ifndef GAME_H
#define GAME_H

#include "GameWindow.h"
#include "Bird.h"
#include "Score.h"
#include "Tower.h"
#include <widgets/Button.h>
#include <vector>

class Game
{
public:
    Game(int width = 800, int height = 600);

    void run();

private:
    GameWindow window;
    Bird bird;
    Score score;
    std::vector<Tower> towers;
    std::vector<TDT4102::Button> themeButtons;

    bool gameOver = false;
    bool scoreHasBeenSaved = false;
    int currentTheme = 0;
    int current_time = 0;

    void birdThemeCallback();

    void fishThemeCallback();

    void alienThemeCallback();

    void processInput();

    void update();

    void render();

    void spawnObstacle();

    void reset();

    void handleThemeSelection(int themeIndex);

    void initButtons();

    void showButtons();

    std::string formatCurrentScore() const;

    TDT4102::Point textLocation{50, window.height() / 4};
    TDT4102::Image waitingScreen = TDT4102::Image("./assets/WaitingScreen.png");
    // TDT4102::Image waitingScreen = TDT4102::Image("../assets/WaitingScreen.png");
    std::string newHighscore = "GRATULERER! NY REKORD!";
    TDT4102::Color error = TDT4102::Color::dark_red;
    TDT4102::Color success = TDT4102::Color::green;
    TDT4102::Color white = TDT4102::Color::white;
    TDT4102::Color black = TDT4102::Color::black;

    int fontSize = 20;
    TDT4102::Font font = TDT4102::Font::courier_bold_italic;
};

#endif // GAME_H
