#pragma once

#ifndef CHESS_BOARDSPOT_H
#define CHESS_BOARDSPOT_H

#include <memory>
#include "model/pieces/Piece.h"


class BoardSpot {
private:
    int row;
    int column;
    std::unique_ptr<Piece> piece;
public:
    BoardSpot(int row, int column, std::unique_ptr<Piece> piece);

    void setPosition(int newRow, int newColumn);
    int getRow() const;
    int getColumn() const;




};


#endif //CHESS_BOARDSPOT_H
