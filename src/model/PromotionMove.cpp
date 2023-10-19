#include "model/PromotionMove.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/King.h"

bool PromotionMove::makeIfIsLegal(Board &) {
    if (std::dynamic_pointer_cast<Pawn>(transformationSpot->getPiece()) == nullptr) return false;
    if (std::dynamic_pointer_cast<Pawn>(newPiece) != nullptr) return false;
    if (std::dynamic_pointer_cast<King>(newPiece) != nullptr) return false;
    if (transformationSpot->getPieceColour() != newPiece->getColour()) return false;
    if (transformationSpot->getPieceColour() == BLACK && transformationSpot->getRow() != 0) return false;
    if (transformationSpot->getPieceColour() == WHITE && transformationSpot->getRow() != 7) return false;
    swapPieces();
    wasMade = true;
    return true;
}

bool PromotionMove::revertIfWasMade(Board &) {
    if (!wasMade) return false;
    swapPieces();
    wasMade = false;
    return true;
}

PromotionMove::PromotionMove(std::shared_ptr<BoardSpot> &transformationSpot, std::shared_ptr<Piece> &piece)
        : transformationSpot(transformationSpot), newPiece(piece) {


}

void PromotionMove::swapPieces() {
    std::shared_ptr<Piece> tmp = transformationSpot->replacePiece(newPiece);
    newPiece = tmp;
}


