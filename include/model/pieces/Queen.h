#pragma once




#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Colour initColour = WHITE);
    ~Queen() override;

    bool canMoveTo(const Board& board, const BoardSpot &start, const BoardSpot &end) const override;

    std::string getTexturePath() const override;
private:
    static bool isPieceAllowedToMove(const BoardSpot &start, const BoardSpot &end);
    bool isMoveBlocked(const Board &board, const BoardSpot &start, const BoardSpot &end) const;
    bool isSpotOccupiedByAlly(const BoardSpot &spot) const;
    static bool exsistsPieceBetweenStartAndEnd(const Board &board, const BoardSpot &start, const BoardSpot &end);
};



