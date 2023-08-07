#include <gtest/gtest.h>
#include "model/pieces/Queen.h"
#include "model/Board.h"

class QueenTest : public testing::Test{

protected:
    std::shared_ptr<Queen> p;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;

    QueenTest() {}

    virtual ~QueenTest() {

    }

    virtual void SetUp() {
        p = std::make_shared<Queen>(WHITE);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};

TEST_F(QueenTest,MovingTest) {
    //given


    //when




    spot = board.getSpot(4,4);
    spot->replacePiece(p);

    testSpot = board.getSpot(2,3);

    //then

    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(6,5);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(0,0);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,1);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(1,7);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,7);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,0);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,4);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(0,4);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
}


TEST_F(QueenTest,MovingThroughOccupiedSpotsTest) {
    //given

    std::shared_ptr<Queen> p2 = std::make_shared<Queen>(WHITE);
    //when


    spot = board.getSpot(4,4);
    spot->replacePiece(p);

    testSpot = board.getSpot(0,0);

    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(3,3);

//    then
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    testSpot2 = board.getSpot(5,5);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(7,1);
    testSpot2 = board.getSpot(5,3);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(1,7);
    testSpot2 = board.getSpot(3,5);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(4,7);
    testSpot2 = board.getSpot(4,5);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,4);
    testSpot2 = board.getSpot(6,4);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,0);
    testSpot2 = board.getSpot(4,2);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(0,4);
    testSpot2 = board.getSpot(2,4);

    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));


}

