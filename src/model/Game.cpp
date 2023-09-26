#include <iostream>
#include "model/Game.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Knight.h"
#include "model/pieces/Bishop.h"
#include "model/pieces/Queen.h"
#include "model/PromotionMove.h"

Game::Game(Board &gameBoard) : gameBoard(&gameBoard) {
    turnColour = WHITE;
    visibleMove = 0;
}

bool Game::playerMove(int srcX, int srcY, int dstX, int dstY) {

    std::shared_ptr<BoardSpot> srcSpot = gameBoard->getSpot(srcX, srcY);
    if (turnColour != srcSpot->getPieceColour()) {
        return false;
    }

    std::shared_ptr<BoardSpot> dstSpot = gameBoard->getSpot(dstX, dstY);
    std::unique_ptr<Move> move = std::make_unique<RegularMove>(srcSpot, dstSpot);

    if (move->makeIfIsLegal(*gameBoard)) {
        changeTurnColour();
        moves.emplace_back(std::move(move));
        visibleMove++;
        return true;
    }
    return false;
}

void Game::resetGame() {
    moves.clear();
    gameBoard->initBoard();
    visibleMove = 0;
    turnColour = WHITE;

}

void Game::rewindLastMove() {
    if (visibleMove > 0) {
        turnColour = NO_COLOUR;
    }
    if (visibleMove > 0) {
        if (moves[visibleMove - 1]->revertIfWasMade(*gameBoard)) {
            visibleMove--;
        }
    }
}


void Game::rewindAllMoves() {
    if (visibleMove > 0) {
        turnColour = NO_COLOUR;
    }
    while (visibleMove > 0) {
        if (moves[visibleMove - 1]->revertIfWasMade(*gameBoard)) {
            visibleMove--;
        }
    }

}

void Game::forwardOneMove() {
    if (visibleMove < moves.size()) {
        visibleMove++;
        if (moves[visibleMove - 1]->makeIfIsLegal(*gameBoard)) {
        } else {
            visibleMove--;
        }
    }
    if (visibleMove == moves.size()) turnColour = (visibleMove % 2) ? BLACK : WHITE;
}

void Game::forwardAllMoves() {
    while (visibleMove < moves.size()) {
        visibleMove++;
        if (moves[visibleMove - 1]->makeIfIsLegal(*gameBoard)) {
        } else {
            visibleMove--;
        }
    }
    turnColour = (visibleMove % 2) ? BLACK : WHITE;

}

Colour Game::getTurnColour() const {
    return turnColour;
}

void Game::makePromotionMove(int srcX, int srcY, int pieceID) {
    if (srcX != 7 && srcX != 0) return;
    std::shared_ptr<Piece> newPiece;
    std::shared_ptr<BoardSpot> promotionSpot = gameBoard->getSpot(srcX, srcY);
    if (pieceID == 3) {
        newPiece = std::make_shared<Knight>(promotionSpot->getPieceColour());
    } else  if (pieceID == 2) {
        newPiece = std::make_shared<Bishop>(promotionSpot->getPieceColour());
    } else  if (pieceID == 0) {
        newPiece = std::make_shared<Rook>(promotionSpot->getPieceColour());
    } else {
        newPiece = std::make_shared<Queen>(promotionSpot->getPieceColour());
    }

    std::unique_ptr<Move> promotion = std::make_unique<PromotionMove>(promotionSpot, newPiece);
    promotion->makeIfIsLegal(*gameBoard);
    moves.emplace_back(std::move(promotion));
}

void Game::changeTurnColour() {
    turnColour = (turnColour == WHITE) ? BLACK : WHITE;
}

Game::~Game() {
}
