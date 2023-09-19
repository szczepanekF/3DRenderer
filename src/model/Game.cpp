#include "model/Game.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Knight.h"
#include "model/pieces/Bishop.h"
#include "model/pieces/Queen.h"
#include "model/PromotionMove.h"

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
    std::unique_ptr<Move> move = std::make_unique<RegularMove>(srcSpot, dstSpot);

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
        moves[visibleMove]->revertIfWasMade(gameBoard);
        visibleMove--;
    }
}


void Game::rewindAllMoves() {
    while (visibleMove > 0) {
        moves[visibleMove]->revertIfWasMade(gameBoard);
        visibleMove--;
    }
}

void Game::forwardOneMove() {
    if (visibleMove < moves.size()) {
        visibleMove++;
        moves[visibleMove]->makeIfIsLegal(gameBoard);
    }
}

void Game::forwardAllMoves() {
    while (visibleMove < moves.size()) {
        visibleMove++;
        moves[visibleMove]->makeIfIsLegal(gameBoard);
    }
}

Colour Game::getTurnColour() const {
    return turnColour;
}

void Game::makePromotionMove(int srcX, int srcY, int pieceID) {
    if (srcX != 7 && srcX != 0) return;
    std::shared_ptr<Piece> newPiece;
    std::shared_ptr<BoardSpot> promotionSpot = gameBoard.getSpot(srcX, srcY);
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
    promotion->makeIfIsLegal(gameBoard);
    moves.emplace_back(std::move(promotion));
}

Game::~Game() = default;
