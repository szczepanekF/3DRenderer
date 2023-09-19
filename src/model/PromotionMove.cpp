#include "model/PromotionMove.h"
#include "model/pieces/Pawn.h"

bool PromotionMove::makeIfIsLegal([[maybe_unused]] Board &board) {
    if (std::dynamic_pointer_cast<Pawn>(transformationSpot->getPiece()) == nullptr) return false;
    if (transformationSpot->getPieceColour() != newPiece->getColour()) return false;
    swapPieces();
    wasMade = true;
    return true;
}

bool PromotionMove::revertIfWasMade([[maybe_unused]] Board &board) {
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


