#pragma once

#include "MoveSensitivePiece.h"


class BoardSpot;
class Board;
class King : public MoveSensitivePiece {
public:
    std::string getTexturePath() const override;

public:
    King(Colour initColour = WHITE);
    ~King() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;
    bool canCastleTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const;

private:
    static bool isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) ;
    bool isSpotOccupiedByAlly(const BoardSpot &spot) const;

    bool isCastlingPossible(const int offsetX, const int offsetY) const;
    static bool isRookValidForCastling(const BoardSpot &rookSpot) ;
    bool isCastlingBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const;

};


