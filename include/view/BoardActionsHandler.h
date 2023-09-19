#pragma once

#include <SFML/Graphics.hpp>
#include "model/Game.h"



class BoardActionsHandler {
public:
    BoardActionsHandler(const int textureSize);


    void onPressAction(sf::RenderWindow &window);
    void onReleaseAction(sf::RenderWindow &window);
    void updateBoard(sf::RenderWindow &window);

private:
    const std::string whitePromotionKey = "whitePromotion";
    const std::string blackPromotionKey = "blackPromotion";

    int textureSize = 100;
    bool promotionChoice = false;
    Board gameBoard;
    Game chessGame = Game(gameBoard);

    std::map<std::string, sf::Texture> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;

    std::pair<int, int> oldPosIndex = {-1, -1};
    std::pair<int, int> mousePos = {0, 0};
    std::pair<int, int> lastMoveInd = {-1, -1};

    void updateMousePos(sf::RenderWindow &window);
    void drawPromotionChoice(sf::RenderWindow &window);

    void loadTextures();
    bool checkForPromotion(int srcX, int srcY);
    void handlePromotionChoice(int mouseX, int mouseY);
    void setupPromotionSprite();





};
