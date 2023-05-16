#pragma once


#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece{
public:
    Rook(Colour initColour = WHITE);
    ~Rook() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;
};


#endif //CHESS_ROOK_H
