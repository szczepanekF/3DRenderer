#include <gtest/gtest.h>
#include "model/pieces/King.h"
#include "model/BoardSpot.h"


TEST(KingTest, ConstructionTest) {
    //given
//    std::shared_ptr<Piece> king = std::shared_ptr<King>();
    BoardSpot position(0, 1, nullptr);

    //when
    ASSERT_EQ(position.getRow(),0);
    //then
    ASSERT_EQ(position.getRow(),0);


}
