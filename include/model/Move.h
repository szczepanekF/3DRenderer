#pragma once

#include "BoardSpot.h"
class Move {


public:
    Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot);
    bool canBeMade(const Board &board);

private:
    std::shared_ptr<BoardSpot> fromSpot;
    std::shared_ptr<BoardSpot> toSpot;
    std::shared_ptr<Piece> takenPiece;
    std::shared_ptr<Piece> movingPiece;

    bool areSameColour();
};

