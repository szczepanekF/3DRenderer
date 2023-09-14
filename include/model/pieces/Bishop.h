#pragma once


#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Colour initColour = WHITE);
    ~Bishop() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;

    std::string getTexturePath() const override;

};


