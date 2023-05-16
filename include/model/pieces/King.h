#pragma once

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"


class BoardSpot;
class Board;
class King : public Piece{
private:
    bool castlingAvailable;

public:
    King(Colour initColour = WHITE);
    ~King() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;
};


#endif //CHESS_KING_H
