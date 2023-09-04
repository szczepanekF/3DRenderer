
#include "model/Game.h"

Game::Game(const Board &gameBoard) : gameBoard(gameBoard) {
    turnColor = WHITE;
    visibleMove = 0;
}

void Game::turn() {

}

bool Game::playerMove(int srcX, int srcY, int dstX, int dstY) {
    std::shared_ptr<BoardSpot> srcSpot = gameBoard.getSpot(srcX, srcY);
    if (turnColor != srcSpot->getPieceColour()) {
        return false;
    }

    std::shared_ptr<BoardSpot> dstSpot = gameBoard.getSpot(dstX, dstY);
    std::unique_ptr<Move> move = std::make_unique<Move>(srcSpot, dstSpot);
    if (move->isLegal(gameBoard)) {
        move->make();
        moves.emplace_back(std::move(move));
        turnColor = srcSpot->getPieceOppositeColour();
        return true;
    }
    return false;
}

bool Game::isMoveValid() {
    return false;
}



void Game::resetGame() {
    gameBoard.initBoard();
    moves.clear();
    visibleMove = 0;
    turnColor = WHITE;
}

void Game::rewindLastMove() {
    if (visibleMove > 0) {
        moves[visibleMove]->revert();
        visibleMove--;
    }
}


void Game::rewindAllMoves() {
    while (visibleMove > 0) {
        moves[visibleMove]->revert();
        visibleMove--;
    }
}

void Game::forwardOneMove() {
    if (visibleMove < moves.size()) {
        visibleMove++;
        moves[visibleMove]->make();
    }
}

void Game::forwardAllMoves() {
    while (visibleMove < moves.size()) {
        visibleMove++;
        moves[visibleMove]->make();
    }
}

Game::~Game() = default;
