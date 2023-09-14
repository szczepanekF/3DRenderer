#pragma once

#include <string>

enum Colour{
    WHITE,
    BLACK,
    NO_COLOUR
};

class BoardSpot;
class Board;
class Piece {
public:
    Piece(Colour initColour = WHITE);
    virtual ~Piece() = default;

    virtual bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const =0;
    virtual bool canTake(const Board& board, const BoardSpot &start, const BoardSpot &end) const;

    Colour getColour() const;
    Colour getOppositeColour() const;
    virtual std::string getTexturePath() const;
private:
    Colour colour = WHITE;
};



