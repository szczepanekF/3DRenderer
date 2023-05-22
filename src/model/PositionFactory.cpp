
#include <iostream>
#include "model/PositionFactory.h"
#include "model/pieces/King.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Bishop.h"
#include "model/pieces/Knight.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Queen.h"


Colour PositionFactory::sideColour;

PositionFactory::PositionFactory() {

}

std::shared_ptr<BoardSpot> PositionFactory::createBlankPosition(int row, int col) {
    return std::make_shared<BoardSpot>(row, col, nullptr);
}

std::shared_ptr<BoardSpot> PositionFactory::createKingPosition(int row, int col) {
    std::unique_ptr<Piece> king = std::make_unique<King>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(king));
}

std::shared_ptr<BoardSpot> PositionFactory::createPawnPosition(int row, int col) {
    std::unique_ptr<Piece> pawn = std::make_unique<Pawn>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(pawn));
}

std::shared_ptr<BoardSpot> PositionFactory::createBishopPosition(int row, int col) {
    std::unique_ptr<Piece> bishop = std::make_unique<Bishop>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(bishop));
}

std::shared_ptr<BoardSpot> PositionFactory::createKnightPosition(int row, int col) {
    std::unique_ptr<Piece> knight = std::make_unique<Knight>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(knight));
}

std::shared_ptr<BoardSpot> PositionFactory::createRookPosition(int row, int col) {
    std::unique_ptr<Piece> rook = std::make_unique<Rook>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(rook));
}

std::shared_ptr<BoardSpot> PositionFactory::createQueenPosition(int row, int col) {
    std::unique_ptr<Piece> queen = std::make_unique<Queen>(sideColour);
    return std::make_shared<BoardSpot>(row, col, std::move(queen));
}

void PositionFactory::setBlackSide() {
    sideColour = BLACK;
}

void PositionFactory::setWhiteSide() {
    sideColour = WHITE;
}

