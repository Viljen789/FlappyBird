#include <iostream>
#include <filesystem>
#include "Game.h"

int main() {
    // Used for finding out which path to use
    // std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    Game flappyBird(800, 600);
    flappyBird.run();
    return 0;
}
