#pragma once
#include <SFML/Graphics.hpp>
#include "BoardActionsHandler.h"
class MainGameView {
public:
    void run();

private:
    const int textureSize = 100;
    sf::RenderWindow window = sf::RenderWindow(
            sf::VideoMode(8 * (unsigned)textureSize, 8 * (unsigned)textureSize), "Chess");
    BoardActionsHandler handler = BoardActionsHandler(textureSize);


    void drawBoard();
};



