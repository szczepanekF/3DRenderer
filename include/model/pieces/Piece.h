#pragma once

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
enum Colour{
    WHITE,
    BLACK
};
class BoardSpot;
class Board;
class Piece {
public:
    Piece(Colour initColour = WHITE);
    virtual ~Piece() = default;

    virtual bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end)=0;
private:
    Colour colour = WHITE;
};


#endif //CHESS_PIECE_H
