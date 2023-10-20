#pragma once

#include "MoveSensitivePiece.h"

class Rook : public MoveSensitivePiece {
public:
    std::string getTexturePath() const override;

public:
    Rook(Colour initColour = WHITE);
    ~Rook() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

private:
    static bool isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) ;
    bool isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    bool isSpotOccupiedByAlly(const BoardSpot &spot) const;
    static bool exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) ;
};



