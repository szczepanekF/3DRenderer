#pragma once


#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece{
public:
    Rook();
    ~Rook() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;
};


#endif //CHESS_ROOK_H
