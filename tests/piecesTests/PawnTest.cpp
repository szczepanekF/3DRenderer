#include <gtest/gtest.h>
#include "model/pieces/Pawn.h"
#include "model/BoardSpot.h"
#include "model/Board.h"

class PawnTest : public ::testing::Test {

protected:
    std::shared_ptr<Pawn> p;
    std::shared_ptr<Pawn> p2;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;


    PawnTest() {
    }

    virtual ~PawnTest() {
    }

    virtual void SetUp() {
        p = std::make_shared<Pawn>(WHITE);
        p2 = std::make_shared<Pawn>(BLACK);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};


TEST_F(PawnTest, ConstructionTest) {
    //given

    //when

    //then
    EXPECT_EQ(p->getColour(), WHITE);
    EXPECT_EQ(p2->getColour(), BLACK);
}

TEST_F(PawnTest, MovingToBlankSpotTest) {
    //given

    //when
    spot = board.getSpot(3, 4);
    spot->replacePiece(p);

    testSpot = board.getSpot(3, 3);
    //then
    EXPECT_TRUE(spot->isOccupied());


    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(4, 5);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(4, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(5, 4);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(6, 4);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 4);
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    spot->replacePiece(nullptr);
    spot = board.getSpot(4, 4);
    spot->replacePiece(p2);


    EXPECT_TRUE(p2->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(3, 4);
    EXPECT_TRUE(p2->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(1, 4);
    EXPECT_FALSE(p2->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(5, 4);
    EXPECT_FALSE(p2->canMoveTo(board, *spot, *testSpot));
}

TEST_F(PawnTest, MovingToOccupiedSpotTest) {
    //given

    //when

    spot = board.getSpot(3, 4);
    spot->replacePiece(p);

    testSpot = board.getSpot(4, 4);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(5, 4);
    testSpot->replacePiece(p2);
    //then
    EXPECT_TRUE(testSpot->isOccupied());
    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot));

    EXPECT_FALSE(p->canMoveTo(board, *spot, *testSpot2));
    testSpot->replacePiece(nullptr);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot2));
    testSpot2->replacePiece(p2);


    EXPECT_FALSE(p2->canMoveTo(board, *testSpot2, *spot));
    spot->replacePiece(nullptr);


    EXPECT_TRUE(p2->canMoveTo(board, *testSpot2, *spot));
    testSpot->replacePiece(p);
    EXPECT_FALSE(p2->canMoveTo(board, *testSpot2, *spot));
    EXPECT_FALSE(p2->canMoveTo(board, *testSpot2, *testSpot));


    //takes Test
    testSpot = board.getSpot(4, 5);
    testSpot->replacePiece(p2);
    EXPECT_TRUE(p->canMoveTo(board, *spot, *testSpot));
}


TEST_F(PawnTest, WhiteTakingTest) {
    //given

    //when
    spot = board.getSpot(3, 3);
    spot->replacePiece(p);

    testSpot = board.getSpot(4, 4);
    //then

    EXPECT_TRUE(p->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(4, 2);
    EXPECT_TRUE(p->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(3, 2);
    EXPECT_FALSE(p->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(3, 4);
    EXPECT_FALSE(p->canTake(board, *spot, *testSpot));

}

TEST_F(PawnTest, BlackTakingTest) {
    //given

    //when
    spot = board.getSpot(3, 3);
    spot->replacePiece(p2);

    testSpot = board.getSpot(4, 4);

    //then

    EXPECT_FALSE(p2->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(4, 2);
    EXPECT_FALSE(p2->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 2);
    EXPECT_TRUE(p2->canTake(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 4);
    EXPECT_TRUE(p2->canTake(board, *spot, *testSpot));

}