
#include "model/PositionFactory.h"
#include "model/pieces/King.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Bishop.h"
#include "model/pieces/Knight.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Queen.h"

std::shared_ptr<BoardSpot> PositionFactory::createBlankPosition(int row, int col) {
    return std::make_shared<BoardSpot>(row, col, nullptr);
}

std::shared_ptr<BoardSpot> PositionFactory::createKingPosition(int row, int col) {
    std::unique_ptr<Piece> king = std::make_unique<King>();
    return std::make_shared<BoardSpot>(row, col, std::move(king));
}

std::shared_ptr<BoardSpot> PositionFactory::createPawnPosition(int row, int col) {
    std::unique_ptr<Piece> pawn = std::make_unique<Pawn>();
    return std::make_shared<BoardSpot>(row, col,std::move(pawn));
}

std::shared_ptr<BoardSpot> PositionFactory::createBishopPosition(int row, int col) {
    std::unique_ptr<Piece> bishop = std::make_unique<Bishop>();
    return std::make_shared<BoardSpot>(row,col, std::move(bishop));
}

std::shared_ptr<BoardSpot> PositionFactory::createKnightPosition(int row, int col) {
    std::unique_ptr<Piece> knight = std::make_unique<Knight>();
    return std::make_shared<BoardSpot>(row,col,std::move(knight));
}

std::shared_ptr<BoardSpot> PositionFactory::createRookPosition(int row, int col) {
    std::unique_ptr<Piece> rook = std::make_unique<Rook>();
    return std::make_shared<BoardSpot>(row,col, std::move(rook));
}

std::shared_ptr<BoardSpot> PositionFactory::createQueenPosition(int row, int col) {
    std::unique_ptr<Piece> queen = std::make_unique<Queen>();
    return std::make_shared<BoardSpot>(row, col, std::move(queen));
}
