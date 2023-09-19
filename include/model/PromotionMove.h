#pragma once

#include "Move.h"
#include "BoardSpot.h"


class PromotionMove : public Move {
public:
    PromotionMove(std::shared_ptr<BoardSpot> &transformationSpot, std::shared_ptr<Piece> &piece);

    bool makeIfIsLegal(Board &board) override;
    bool revertIfWasMade(Board &board) override;
private:
    std::shared_ptr<BoardSpot> transformationSpot;
    std::shared_ptr<Piece> newPiece;
    bool wasMade;
    void swapPieces();

};
