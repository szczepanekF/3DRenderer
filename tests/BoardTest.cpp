#include <gtest/gtest.h>
#include "model/Board.h"

TEST(BoardTest, ConstructionTest) {
    //given
    Board b;
    //when

    //then
    ASSERT_EQ(b.getSpot(-1,0),nullptr);
    ASSERT_EQ(b.getSpot(0,-1),nullptr);
    ASSERT_EQ(b.getSpot(8,0),nullptr);
    ASSERT_EQ(b.getSpot(0,8),nullptr);
}
