#include <gtest/gtest.h>
#include "model/pieces/Knight.h"
#include "model/Board.h"


class KnightTest : public testing::Test {

protected:
    std::shared_ptr<Knight> p;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;

    KnightTest() {}


    virtual ~KnightTest()  {

    }

    virtual void SetUp() {
        p = std::make_shared<Knight>(WHITE);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};

TEST_F(KnightTest,MoveToBlankSpotTest) {
    //given


    //when




    spot = board.getSpot(3,4);
    spot->replacePiece(p);

    testSpot = board.getSpot(3,3);

    //then

    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,3);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,4);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(1,3);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(1,5);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,2);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,6);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(5,3);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(5,5);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,2);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,6);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

}
TEST_F(KnightTest, MoveToOccupiedSpotTest) {
    //given

    std::shared_ptr<Knight> p2 = std::make_shared<Knight>(WHITE);

    //when


    spot = board.getSpot(3,4);
    spot->replacePiece(p);

    testSpot = board.getSpot(1,3);

    //then
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot->replacePiece(nullptr);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

}