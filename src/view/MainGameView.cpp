
#include "view/MainGameView.h"

void MainGameView::run() {


    while (window.isOpen()) {

        window.clear();
        drawBoard();
        handler.updateBoard(window);
        window.display();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                handler.onKeyboardPressAction(event);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                handler.onMousePressAction(window);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                handler.onMouseReleaseAction(window);
            }
        }


    }
}

void MainGameView::drawBoard() {
    std::string boardTexturePath = "../../images/Board.png";
    sf::Texture boardTexture;
    boardTexture.loadFromFile(boardTexturePath);
    sf::Sprite boardPNG;
    boardPNG.setTexture(boardTexture);
    window.draw(boardPNG);
}




