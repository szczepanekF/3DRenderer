#pragma once


#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "Piece.h"

class Pawn : public Piece{
public:
    Pawn(Colour initColour = WHITE);
    ~Pawn() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;

};


#endif //CHESS_PAWN_H
