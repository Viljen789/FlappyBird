#ifndef GAME_H
#define GAME_H

#include "AnimationWindow.h"
#include "Bird.h"
#include "Tower.h"


class Game {
public:
    Game(int width = 800, int height = 600);

    void run();

    // void birdButtonCallback();
    //
    // void fishButtonCallback();
    //
    // void alienButtonCallback();

private:
    TDT4102::AnimationWindow window;
    Bird bird;
    std::vector<Tower> towers;

    bool gameOver = false;
    int score = 0;

    void processInput();

    void update();

    void render();

    void spawnObstacle();

    void reset();

    TDT4102::Point textLocation {50, window.height() / 3};
    std::string fail = "Game over :( Trykk ENTER for å starte på nytt";
    std::string newHighscore = "Gratulerer! Ny rekord!";
    TDT4102::Color textColor = TDT4102::Color::dark_red;
    int fontSize = 40;
    TDT4102::Font font = TDT4102::Font::courier_bold_italic;
    // TDT4102::Point birdLocation{window.width() / 4 * 1, window.height() / 3 * 2};
    // TDT4102::Point fishLocation{window.width() / 4 * 2, window.height() / 3 * 2};
    // TDT4102::Point alienLocation{window.width() / 4 * 3, window.height() / 3 * 2};

};

#endif //GAME_H
