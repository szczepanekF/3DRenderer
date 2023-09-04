
#include "model/Game.h"

void Game::turn() {

}

bool Game::playerMove(int srcX, int srcY, int dstX, int dstY) {
    std::shared_ptr<BoardSpot> srcPiece = gameBoard.getSpot(srcX, srcY);
    if (colourTurn != srcPiece->getPieceColour()) {
        return false;
    }

    std::shared_ptr<BoardSpot> dstPiece = gameBoard.getSpot(dstX, dstY);
    std::unique_ptr<Move> move = std::make_unique<Move>(srcPiece, dstPiece);
    return move->isLegal(gameBoard);
}

bool Game::isMoveValid() {
    return false;
}

Game::Game(const Board &gameBoard) : gameBoard(gameBoard) {}

void Game::resetGame() {
    gameBoard.initBoard();
    moves.clear();
}

Game::~Game() = default;
