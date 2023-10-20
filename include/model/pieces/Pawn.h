#pragma once

#include <utility>
#include "MoveSensitivePiece.h"


class Pawn : public MoveSensitivePiece {

public:
    Pawn(Colour initColour = WHITE);
    ~Pawn() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;
    bool canTake(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;

    std::string getTexturePath() const override;

private:
    bool isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) const;
    bool isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    bool isSpotOccupiedByAlly(const BoardSpot &spot) const;
    bool egsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    int getMovingdirection() const;
};

