#pragma once

class BoardSpot;
class Board;
class Piece;
class Move {


public:
    Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot);
    bool canBeMade(const Board &board);
    void make();
    void revert();

private:
    std::shared_ptr<BoardSpot> fromSpot;
    std::shared_ptr<BoardSpot> toSpot;
    std::shared_ptr<Piece> takenPiece;

    bool arePiecesSameColour();
    bool isCastling(const Board &board);
    bool isMovingPieceKing();
};

