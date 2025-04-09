#include <iostream>
#include <filesystem>
#include "Game.h"

int main()
{
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    Game flappyBird(800,600);
    flappyBird.run();
    return 0;
}
