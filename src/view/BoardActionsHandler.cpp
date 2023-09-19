
#include <iostream>
#include "view/BoardActionsHandler.h"
#include "model/Game.h"
#include "model/pieces/Pawn.h"

BoardActionsHandler::BoardActionsHandler(const int textureSize) : textureSize(textureSize) {
    loadTextures();
}

void BoardActionsHandler::loadTextures() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            std::string texturePath = gameBoard.getSpotTexturePath(i, j);
            if (texturePath.empty()) {
                continue;
            }
            textureMap[texturePath].loadFromFile(texturePath);
            spriteMap[texturePath].setTexture(textureMap[texturePath]);
        }
    }
    textureMap[whitePromotionKey].loadFromFile("../../images/white/Transformation.png");
    spriteMap[whitePromotionKey].setTexture(textureMap[whitePromotionKey]);
    textureMap[blackPromotionKey].loadFromFile("../../images/black/Transformation.png");
    spriteMap[blackPromotionKey].setTexture(textureMap[blackPromotionKey]);

}

void BoardActionsHandler::updateBoard(sf::RenderWindow &window) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            std::string texturePath = gameBoard.getSpotTexturePath(i, j);
            if (i == oldPosIndex.first && j == oldPosIndex.second) {
                continue;
            }
            if (promotionChoice && i == lastMoveInd.first && j == lastMoveInd.second) {
                continue;
            }
            spriteMap[texturePath].setPosition((float) (textureSize * j),
                                               (float) (textureSize * (BOARD_LENGTH - i - 1)));

            window.draw( spriteMap[texturePath]);
        }
    }
    if (oldPosIndex.first != -1 && oldPosIndex.second != -1) {
        updateMousePos(window);
        std::string oldTexturePath = gameBoard.getSpotTexturePath(oldPosIndex.first, oldPosIndex.second);
        spriteMap[oldTexturePath].setPosition((float) mousePos.first,
                                              (float) mousePos.second);
        window.draw(spriteMap[oldTexturePath]);
    }

    if (promotionChoice) {
        drawPromotionChoice(window);
    }
}

void BoardActionsHandler::updateMousePos(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;

    mousePos = {x - textureSize / 2, y - textureSize / 2};

}

void BoardActionsHandler::drawPromotionChoice(sf::RenderWindow &window) {
    if (chessGame.getTurnColour() == WHITE) {
        window.draw(spriteMap[blackPromotionKey]);
    } else {
        window.draw(spriteMap[whitePromotionKey]);
    }
}

void BoardActionsHandler::onPressAction(sf::RenderWindow &window) {
    if (!promotionChoice) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x;
        int y = pos.y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            oldPosIndex = {BOARD_LENGTH - y / textureSize - 1, x / textureSize};
            if (gameBoard.getSpot(oldPosIndex.first, oldPosIndex.second)
                        ->getPieceColour() != chessGame.getTurnColour()) {
                oldPosIndex = {-1, -1};
            }
        }
    }
}

void BoardActionsHandler::onReleaseAction(sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    int x = pos.x;
    int y = pos.y;
    if (promotionChoice) {
        handlePromotionChoice(x,y);
        return;
    }

    if (oldPosIndex.first == -1 || oldPosIndex.second == -1) {
        return;
    }

    lastMoveInd = {BOARD_LENGTH - 1 - y / textureSize , x / textureSize};

    if (chessGame.playerMove(oldPosIndex.first, oldPosIndex.second,
                             lastMoveInd.first, lastMoveInd.second)) {
        if (checkForPromotion(lastMoveInd.first,lastMoveInd.second)) {
            promotionChoice = true;
            setupPromotionSprite();
        } else {
            promotionChoice = false;
        }
    }

    oldPosIndex = {-1, -1};
}

void BoardActionsHandler::handlePromotionChoice(int mouseX, int mouseY) {
    int x = BOARD_LENGTH - 1 - mouseY / textureSize;
    int y = mouseX / textureSize;
    if (x != lastMoveInd.first || y != lastMoveInd.second) {
        return;
    }
    int halfOfTexture = textureSize / 2;
    int halfXChoice =  mouseX % textureSize / halfOfTexture;
    int halfYChoice = mouseY % textureSize / halfOfTexture;
    halfYChoice += (halfYChoice > 0) ? 1 : 0;
    int choice = halfXChoice + halfYChoice;
    std::cout<<"choice: " << choice << '\n';
    chessGame.makePromotionMove(x, y, choice);
    promotionChoice = false;
}

bool BoardActionsHandler::checkForPromotion(int srcX, int srcY) {
    if (srcX != 0 && srcX != 7) {
        return false;
    }
    std::shared_ptr<BoardSpot> spot = gameBoard.getSpot(srcX, srcY);
    std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(spot->getPiece());
    if (pawn != nullptr) {
        return true;
    }
    return false;
}

void BoardActionsHandler::setupPromotionSprite() {
    std::string spriteKey;
    if (chessGame.getTurnColour() == WHITE) {
        spriteKey = blackPromotionKey;
    } else {
        spriteKey = whitePromotionKey;
    }
    int x = (lastMoveInd.second) * textureSize;
    int y = (BOARD_LENGTH - lastMoveInd.first - 1) * textureSize;
    spriteMap[spriteKey].setPosition((float) x, (float) y);
}







