#pragma once


#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Colour initColour = WHITE);
    ~Bishop() override;

    bool canMoveTo(const Board &board, const BoardSpot &start, const BoardSpot &end) const override;
    std::string getTexturePath() const override;

private:
    static bool isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end) ;
    bool isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    bool isSpotOccupiedByAlly(const BoardSpot &spot) const;
    static bool exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end) ;
};


