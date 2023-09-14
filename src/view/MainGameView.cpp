
#include "view/MainGameView.h"

void MainGameView::run()  {



    while( window.isOpen() )
    {

        window.clear();
        drawBoard();
        handler.updateBoard(window);

        sf::Event event;
        while( window.pollEvent( event ) ) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }



            if (event.type == sf::Event::MouseButtonPressed) {
                handler.onPressAction(window);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                handler.onReleaseAction(window);
            }

        }


        window.display();

    }
}

void MainGameView::drawBoard()  {
    std::string boardTexturePath = "../../images/Board.png";
    sf::Texture boardTexture;
    boardTexture.loadFromFile(boardTexturePath);
    sf::Sprite boardPNG;
    boardPNG.setTexture(boardTexture);
    window.draw(boardPNG);
}




