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

TEST(BoardTest, InitTest) {
    //given
    Board b;
    //when
    b.initBoard();
    //then

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_NE(b.getSpot(i,j),nullptr);
        }
    }
}
