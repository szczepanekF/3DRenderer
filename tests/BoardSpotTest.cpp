#include <gtest/gtest.h>
#include "model/BoardSpot.h"


TEST(PositionTest, ConstructionTest) {
    //given

    BoardSpot position(0, 4, nullptr);


    //when

    //then
    ASSERT_EQ(position.getRow(), 0);
    ASSERT_EQ(position.getColumn(), 4);

}