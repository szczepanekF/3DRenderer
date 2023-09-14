#include "view/BoardActionsHandler.h"
#include "model/Game.h"

BoardActionsHandler::BoardActionsHandler(const int textureSize) : textureSize(textureSize) {}

void BoardActionsHandler::onPressAction(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        oldPosIndex = {BOARD_LENGTH - y / textureSize - 1, x / textureSize};
    }

}

void BoardActionsHandler::onReleaseAction(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;
    std::pair<int, int> newPosIndex = {BOARD_LENGTH - y / textureSize - 1, x / textureSize};

    chessGame.playerMove(oldPosIndex.first, oldPosIndex.second,
                         newPosIndex.first, newPosIndex.second);

    oldPosIndex = {-1, -1};
}

void BoardActionsHandler::updateBoard(sf::RenderWindow &window) {
    updateMousePos(window);
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            std::string texturePath = gameboard.getSpotTexturePath(i, j);
            if (texturePath.empty()) {
                textureBoard[i][j] = sf::Texture();
                continue;
            }

            textureBoard[i][j].loadFromFile(texturePath);

            spriteBoard[i][j].setTexture(textureBoard[i][j]);
            if (i == oldPosIndex.first && j == oldPosIndex.second) {
                spriteBoard[i][j].setPosition((float) mousePos.first, (float) mousePos.second);
            } else {
                spriteBoard[i][j].setPosition((float) (textureSize * j),
                                              (float) (textureSize * (BOARD_LENGTH - i - 1)));
            }
            window.draw(spriteBoard[i][j]);
        }
    }


}

void BoardActionsHandler::updateMousePos(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;

    mousePos = {x - textureSize / 2, y - textureSize / 2};

}

