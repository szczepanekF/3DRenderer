#include "model/Game.h"

Game::Game(const Board &gameBoard) : gameBoard(gameBoard) {
    turnColour = WHITE;
    visibleMove = 0;
}

bool Game::playerMove(int srcX, int srcY, int dstX, int dstY) {
    std::shared_ptr<BoardSpot> srcSpot = gameBoard.getSpot(srcX, srcY);
    if (turnColour != srcSpot->getPieceColour()) {
        return false;
    }

    std::shared_ptr<BoardSpot> dstSpot = gameBoard.getSpot(dstX, dstY);
    std::unique_ptr<Move> move = std::make_unique<Move>(srcSpot, dstSpot);

    std::shared_ptr<Piece> piece = srcSpot->getPiece();
    Colour oppositeColour = piece->getOppositeColour();

    if (move->makeIfIsLegal(gameBoard)) {
        turnColour = oppositeColour;
        moves.emplace_back(std::move(move));
        return true;
    }
    return false;
}

void Game::resetGame() {
    gameBoard.initBoard();
    moves.clear();
    visibleMove = 0;
    turnColour = WHITE;
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

Colour Game::getTurnColour() const {
    return turnColour;
}

Game::~Game() = default;
