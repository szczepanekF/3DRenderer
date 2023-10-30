#pragma once

#include "Move.h"

class BoardSpot;
class Board;
class Piece;
class RegularMove : public Move {


public:
    RegularMove(std::shared_ptr<BoardSpot> fromSpot, std::shared_ptr<BoardSpot> toSpot);
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

    bool isLegalCastling(const Board &board);
    bool arePiecesSameColour() const;
    bool isPieceAvailableToMove(const Board &board);
    bool canPieceLegallyMove(const Board &board);
    bool willKingBeAttacked(Board &board);

    void performCastling(const Board &board);
    void moveKingToCastlingSpot(const Board &board);
    void moveRookToCastlingSpot(const Board &board);
    void unperformCastling(const Board &board);
    void revertCastlingKingMove(const Board &board);
    void revertCastlingRookMove(const Board &board);

    bool isLongPawnMove();
    bool isEnPassant(const Board &board);

    void prepareEnPassant(const Board &board);
    void prepareEnPassantIfNecessary(const Board &board);
    void unprepareEnPassantIfNecessary(const Board &board);
    void unprepareEnpassant(const Board &board);
    void updateBoardEnPassant(Board &board);


};

