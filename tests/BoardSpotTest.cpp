#include <gtest/gtest.h>
#include "model/BoardSpot.h"
#include "model/pieces/King.h"
#include "model/pieces/Pawn.h"


TEST(PositionTest, ConstructionTest) {
    //given

    BoardSpot position(0, 4, nullptr);
    BoardSpot occupiedPosition(0, 4, std::make_shared<Pawn>());

    //when

    //then
    ASSERT_EQ(position.getRow(), 0);
    ASSERT_EQ(position.getColumn(), 4);

    ASSERT_FALSE(position.isOccupied());
    ASSERT_TRUE(occupiedPosition.isOccupied());

}


TEST(PositionTest, ReplaceTest) {
    //given

    BoardSpot position(0, 4, nullptr);


    //when
    std::shared_ptr<Piece> piece = std::make_unique<King>();
    ASSERT_EQ(position.replacePiece(piece), nullptr);

    //then
    ASSERT_EQ(position.getPiece().get(), piece.get());


}