#pragma once

class BoardSpot;
class Board;
class Piece;
class Move {


public:
    Move(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot);
    bool isLegal(const Board &board);
    bool makeIfIsLegal(const Board &board);
    void make();
    void revert();

private:
    std::shared_ptr<BoardSpot> fromSpot;
    std::shared_ptr<BoardSpot> toSpot;
    std::shared_ptr<Piece> takenPiece;
    bool castlingMove;
    void performCastling(const Board &board);
    void unperformCastling(const Board &board);
    bool arePiecesSameColour() const;
    bool isCastling(const Board &board);

};

