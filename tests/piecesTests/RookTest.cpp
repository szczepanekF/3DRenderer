#include <gtest/gtest.h>
#include "model/pieces/Rook.h"
#include "model/Board.h"

class RookTest : public testing::Test {

protected:
    std::shared_ptr<Rook> p;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;

    RookTest() {}

    ~RookTest() override {

    }


    virtual void SetUp() {
        p = std::make_shared<Rook>(WHITE);
        board.clearBoard();
    }

    virtual void TearDown() {

    }

};


TEST_F(RookTest, MoveToBalnkSpotTest) {
    //given
    spot = board.getSpot(4, 4);
    testSpot = board.getSpot(0, 0);

    //when
    spot->replacePiece(p);


    //then
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(7, 7);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(7, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(0, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 0);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 7);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(5, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(3, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 5);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 3);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
}


TEST_F(RookTest, MoveThroughOccupiedSpotTest) {
    //given
    std::shared_ptr<Rook> p2 = std::make_shared<Rook>(WHITE);

    spot = board.getSpot(4, 4);
    testSpot = board.getSpot(0, 4);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(2, 4);

    //when
    spot->replacePiece(p);

    //then

    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2->replacePiece(p2);

    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot2));


    testSpot = board.getSpot(4, 0);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2 = board.getSpot(4, 2);
    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot2));


    testSpot = board.getSpot(4, 7);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2 = board.getSpot(4, 5);
    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot2));


    testSpot = board.getSpot(7, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot2 = board.getSpot(5, 4);
    testSpot2->replacePiece(p2);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot2));
}