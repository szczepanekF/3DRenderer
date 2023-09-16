
#include "view/BoardActionsHandler.h"
#include "model/Game.h"

BoardActionsHandler::BoardActionsHandler(const int textureSize) : textureSize(textureSize) {
    loadTextures();
}

void BoardActionsHandler::onPressAction(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        oldPosIndex = {BOARD_LENGTH - y / textureSize - 1, x / textureSize};

        if (gameboard.getSpot(oldPosIndex.first, oldPosIndex.second)
        ->getPieceColour() != chessGame.getTurnColour()) {
            oldPosIndex = {-1, -1};
        }
    }

}

void BoardActionsHandler::onReleaseAction(sf::RenderWindow &window) {
    if (oldPosIndex.first == -1 || oldPosIndex.second == -1) {
        return;
    }

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;
    std::pair<int, int> newPosIndex = {BOARD_LENGTH - y / textureSize - 1, x / textureSize};

    if (chessGame.playerMove(oldPosIndex.first, oldPosIndex.second,
                         newPosIndex.first, newPosIndex.second)) {
        
    }

    oldPosIndex = {-1, -1};
}


void BoardActionsHandler::updateBoard(sf::RenderWindow &window) {
    updateMousePos(window);

    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {

            std::string texturePath = gameboard.getSpotTexturePath(i, j);
            if (i == oldPosIndex.first && j == oldPosIndex.second) {
                continue;
            }

            spriteMap[texturePath].setPosition((float) (textureSize * j),
                                               (float) (textureSize * (BOARD_LENGTH - i - 1)));

            window.draw( spriteMap[texturePath]);
        }
    }
    if (oldPosIndex.first != -1 && oldPosIndex.second != -1) {
        std::string oldTexturePath = gameboard.getSpotTexturePath(oldPosIndex.first, oldPosIndex.second);
        spriteMap[oldTexturePath].setPosition((float) mousePos.first,
                                              (float) mousePos.second);
        window.draw(spriteMap[oldTexturePath]);
    }




}

void BoardActionsHandler::loadTextures() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            std::string texturePath = gameboard.getSpotTexturePath(i, j);
            if (texturePath.empty()) {
                continue;
            }
            textureMap[texturePath].loadFromFile(texturePath);
            spriteMap[texturePath].setTexture(textureMap[texturePath]);
        }
    }
}

void BoardActionsHandler::updateMousePos(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;

    mousePos = {x - textureSize / 2, y - textureSize / 2};

}


