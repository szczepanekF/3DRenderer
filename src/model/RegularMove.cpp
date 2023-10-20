
#include <utility>

#include "model/Board.h"
#include "model/RegularMove.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Pawn.h"

RegularMove::RegularMove(std::shared_ptr<BoardSpot> fromSpot,
                         std::shared_ptr<BoardSpot> toSpot) : fromSpot(std::move(fromSpot)), toSpot(std::move(toSpot)),
                                                              wasMade(false),
                                                              castlingMove(false), enPassantColBeforeMove(-1) {}


bool RegularMove::makeIfIsLegal(Board &board) {
    enPassantColBeforeMove = board.getEnPassantCol();
    if (isLegal(board) && !wasMade) {
        make(board);
        wasMade = true;
        return true;
    }
    return false;
}

bool RegularMove::revertIfWasMade(Board &board) {
    if (wasMade) {
        board.setEnPassantCol(enPassantColBeforeMove);
        revert(board);
        wasMade = false;
        return true;
    }
    return false;
}

bool RegularMove::isLegal(Board &board) {
    std::shared_ptr<Piece> fromPiece = fromSpot->getPiece();
    if (fromPiece == nullptr) {
        return false;
    }

    if (isLegalCastling(board)) {
        return true;
    }

    if (arePiecesSameColour()) {
        return false;
    }

    if (!isPieceAvailableToMove(board)) {
        return false;
    }
    return !willKingBeAttacked(board);
}

bool RegularMove::isLegalCastling(const Board &board) {
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(fromSpot->getPiece());
    if (king != nullptr) {
        castlingMove = king->canCastleTo(board, *fromSpot, *toSpot);
    }
    return castlingMove;
}

bool RegularMove::arePiecesSameColour() const {
    Colour firstSpotPieceColour = fromSpot->getPieceColour();
    Colour secondSpotPieceColour = toSpot->getPieceColour();
    return firstSpotPieceColour == secondSpotPieceColour;
}

bool RegularMove::isPieceAvailableToMove(const Board &board) {
    prepareEnPassantIfNecessary(board);
    bool isAvailable = canPieceLegallyMove(board);
    unprepareEnPassantIfNecessary(board);
    return isAvailable;
}

void RegularMove::prepareEnPassantIfNecessary(const Board &board) {
    if (isEnPassant(board)) {
        prepareEnPassant(board);
    }
}

void RegularMove::prepareEnPassant(const Board &board) {
    int dir = (fromSpot->getPieceColour() == WHITE) ? -1 : 1;
    std::shared_ptr<BoardSpot> takenPieceSpot = board.getSpot(toSpot->getRow() + dir, toSpot->getColumn());
    toSpot->replacePiece(takenPieceSpot->replacePiece(nullptr));
}

void RegularMove::unprepareEnPassantIfNecessary(const Board &board) {
    if (isEnPassant(board)) {
        unprepareEnpassant(board);
    }
}

void RegularMove::unprepareEnpassant(const Board &board) {
    int dir = (fromSpot->getPieceColour() == WHITE) ? -1 : 1;
    std::shared_ptr<BoardSpot> takenPieceSpot = board.getSpot(toSpot->getRow() + dir, toSpot->getColumn());
    takenPieceSpot->replacePiece(toSpot->replacePiece(nullptr));
}

bool RegularMove::isEnPassant(const Board &board) {
    std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(fromSpot->getPiece());
    if (pawn == nullptr) {
        return false;
    }
    if (board.getEnPassantCol() == toSpot->getColumn() && abs(toSpot->getColumn() - fromSpot->getColumn()) == 1) {
        if ((pawn->getColour() == WHITE && fromSpot->getRow() == 4 && toSpot->getRow() == 5) ||
            (pawn->getColour() == BLACK && fromSpot->getRow() == 3 && toSpot->getRow() == 2)) {
            return true;
        }
    }
    return false;
}

bool RegularMove::canPieceLegallyMove(const Board &board) {
    std::shared_ptr<Piece> fromPiece = fromSpot->getPiece();
    return fromPiece->canMoveTo(board, *fromSpot, *toSpot);
}


bool RegularMove::willKingBeAttacked(Board &board) {
    Colour fromSpotColour = fromSpot->getPieceColour();
    Colour enemyColour = fromSpot->getPieceOppositeColour();

    make(board);
    std::shared_ptr<BoardSpot> kingSpot = board.getKingSpotOfColour(fromSpotColour);
    bool willBeAttacked = (board.isSpotAttackedBy(kingSpot->getRow(), kingSpot->getColumn(), enemyColour));
    revert(board);

    return willBeAttacked;
}

void RegularMove::make(Board &board) {
    if (castlingMove) {
        return performCastling(board);
    }
    prepareEnPassantIfNecessary(board);
    updateBoardEnPassant(board);
    std::shared_ptr<Piece> movingPiece = fromSpot->replacePiece(nullptr);
    std::shared_ptr<MoveSensitivePiece> moveSensitive = std::dynamic_pointer_cast<MoveSensitivePiece>(movingPiece);
    if (moveSensitive != nullptr) {
        moveSensitive->move();
    }
    this->takenPiece = toSpot->replacePiece(movingPiece);
}

void RegularMove::revert(const Board &board) {
    if (castlingMove) {
        return unperformCastling(board);
    }

    std::shared_ptr<Piece> movedPiece = toSpot->replacePiece(this->takenPiece);
    std::shared_ptr<MoveSensitivePiece> moveSensitive = std::dynamic_pointer_cast<MoveSensitivePiece>(movedPiece);
    if (moveSensitive != nullptr) {
        moveSensitive->undoMove();
    }
    fromSpot->replacePiece(movedPiece);
    unprepareEnPassantIfNecessary(board);
}



void RegularMove::performCastling(const Board &board) {

    std::shared_ptr<Piece> movingPiece = fromSpot->replacePiece(nullptr);
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(movingPiece);
    king->move();

    int colDiff = toSpot->getColumn() - fromSpot->getColumn();
    int posDir = (colDiff > 0) ? 1 : -1;
    std::shared_ptr<BoardSpot> newPosition = board.getSpot(fromSpot->getRow(),
                                                           fromSpot->getColumn() + posDir * 2);
    newPosition->replacePiece(king);

    int rookCol = (colDiff > 0) ? 7 : 0;
    std::shared_ptr<BoardSpot> rookSpot = board.getSpot(fromSpot->getRow(), rookCol);
    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot->replacePiece(nullptr));
    rook->move();

    rookSpot = board.getSpot(fromSpot->getRow(), fromSpot->getColumn() + posDir * 1);
    rookSpot->replacePiece(rook);
}

void RegularMove::unperformCastling(const Board &board) {
    int colDiff = toSpot->getColumn() - fromSpot->getColumn();
    int posDir = (colDiff > 0) ? 1 : -1;

    std::shared_ptr<BoardSpot> kingCurrentSpot = board.getSpot(fromSpot->getRow(),
                                                               fromSpot->getColumn() + posDir * 2);

    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(kingCurrentSpot->replacePiece(nullptr));
    king->undoMove();

    fromSpot->replacePiece(king);

    std::shared_ptr<BoardSpot> rookSpot = board.getSpot(fromSpot->getRow(),
                                                        fromSpot->getColumn() + posDir * 1);

    std::shared_ptr<Rook> rook = std::dynamic_pointer_cast<Rook>(rookSpot->replacePiece(nullptr));
    rook->undoMove();

    int rookCol = (colDiff > 0) ? 7 : 0;
    rookSpot = board.getSpot(fromSpot->getRow(), rookCol);
    rookSpot->replacePiece(rook);
}


bool RegularMove::isLongPawnMove() {
    std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(fromSpot->getPiece());
    if (pawn != nullptr) {
        if (abs(fromSpot->getRow() - toSpot->getRow()) == 2) {
            return true;
        }
    }
    return false;
}

void RegularMove::updateBoardEnPassant(Board &board) {
    if (isLongPawnMove()) {
        board.setEnPassantCol(fromSpot->getColumn());
    } else {
        board.setEnPassantCol(-1);
    }

}




