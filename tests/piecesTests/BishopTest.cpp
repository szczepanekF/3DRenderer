#include <gtest/gtest.h>
#include "model/pieces/Bishop.h"
#include "model/Board.h"

class BishopTest : public ::testing::Test {

protected:
    std::shared_ptr<Bishop> p;
    std::shared_ptr<Bishop> p2;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;


    BishopTest() {
    }

    virtual ~BishopTest() {
    }

    virtual void SetUp() {
        p = std::make_shared<Bishop>(WHITE);
        p2 = std::make_shared<Bishop>(BLACK);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};

TEST_F(BishopTest, MovingTest) {
    //given
    spot = board.getSpot(4, 4);
    testSpot = board.getSpot(4, 3);

    //when
    spot->replacePiece(p);

    //then

    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(5, 4);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(7, 7);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(0, 0);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(7, 1);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(1, 7);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
}

TEST_F(BishopTest, MovingTroughOccupiedSpotsTest) {
    //given
    spot = board.getSpot(4, 4);
    std::shared_ptr<BoardSpot> testSpot = board.getSpot(7, 7);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(6, 6);

    //when
    spot->replacePiece(p);

    //then

    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot2));


    testSpot = board.getSpot(7, 1);
    testSpot2 = board.getSpot(6, 2);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot2));
}


