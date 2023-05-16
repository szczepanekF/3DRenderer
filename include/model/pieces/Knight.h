#pragma once

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece{


public:
    Knight(Colour initColour = WHITE);
    ~Knight() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;

};


#endif //CHESS_KNIGHT_H
