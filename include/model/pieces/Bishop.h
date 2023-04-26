#pragma once

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop();
    ~Bishop() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) override;

};


#endif //CHESS_BISHOP_H
