#include "model/BoardSpot.h"
#include "model/pieces/Piece.h"

BoardSpot::BoardSpot(int row, int column, std::unique_ptr<Piece> piece) : row(row), column(column),
                                                                          piece(std::move(piece)) {


}

int BoardSpot::getRow() const {
    return row;
}

int BoardSpot::getColumn() const {
    return column;
}
