#include <gtest/gtest.h>
#include "model/BoardSpot.h"
#include "model/pieces/King.h"


TEST(PositionTest, ConstructionTest) {
    //given

    BoardSpot position(0, 4, nullptr);


    //when

    //then
    ASSERT_EQ(position.getRow(), 0);
    ASSERT_EQ(position.getColumn(), 4);

}


TEST(PositionTest, ReplaceTest) {
    //given

    BoardSpot position(0, 4, nullptr);


    //when
//    std::unique_ptr<Piece> piece = std::make_unique<King>();
//    position.replacePiece(std::move(piece));
    //then
    ASSERT_EQ(position.getRow(), 0);
    ASSERT_EQ(position.getColumn(), 4);

}