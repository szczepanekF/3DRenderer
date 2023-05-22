#pragma once


#include <memory>
#include "pieces/Piece.h"


class BoardSpot {
private:
    int row;
    int column;
    std::shared_ptr<Piece> piece;
public:
    BoardSpot(int row, int column, std::shared_ptr<Piece> piece);

    std::shared_ptr<Piece> replacePiece(std::shared_ptr<Piece> piece);
    bool isOccupied() const;
    Colour getPieceColour() const;
    std::shared_ptr<Piece> getPiece() const;
    int getRow() const;
    int getColumn() const;






};


