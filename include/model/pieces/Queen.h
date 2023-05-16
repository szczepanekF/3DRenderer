#pragma once


#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "Piece.h"

class Queen : public Piece{
public:
    Queen(Colour initColour = WHITE);
    ~Queen() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;
};


#endif //CHESS_QUEEN_H
