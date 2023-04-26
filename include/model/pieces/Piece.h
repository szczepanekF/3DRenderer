#pragma once

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class BoardSpot;
class Board;
class Piece {
public:
    Piece() = default;
    virtual ~Piece() = default;

    virtual bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end)=0;
};


#endif //CHESS_PIECE_H
