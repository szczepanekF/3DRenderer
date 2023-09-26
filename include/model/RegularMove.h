#pragma once

#include "Move.h"

class BoardSpot;
class Board;
class Piece;
class RegularMove : public Move {


public:
    RegularMove(const std::shared_ptr<BoardSpot> &fromSpot, const std::shared_ptr<BoardSpot> &toSpot);
    bool isLegal(Board &board);
    bool makeIfIsLegal(Board &board) override;
    bool revertIfWasMade(Board &board) override;


private:
    std::shared_ptr<BoardSpot> fromSpot;
    std::shared_ptr<BoardSpot> toSpot;
    std::shared_ptr<Piece> takenPiece;
    bool wasMade;
    bool castlingMove;
    int enPassantColBeforeMove;

    void make(Board &board);
    void revert(const Board &board);

    void performCastling(const Board &board);
    void unperformCastling(const Board &board);

    bool isCastling(const Board &board);
    bool arePiecesSameColour() const;
    bool isLongPawnMove();
    bool isEnPassant(const Board &board);

    void prepareEnPassant(const Board &board);
    void unprepareEnpassant(const Board &board);
    void updateBoardEnPassant(Board &board);


};

