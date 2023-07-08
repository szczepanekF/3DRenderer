#include <gtest/gtest.h>
#include "model/pieces/Pawn.h"
#include "model/BoardSpot.h"
#include "model/Board.h"

class PawnTest : public ::testing::Test {

protected:
    std::shared_ptr<Pawn> p = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);

    PawnTest() {
    }

    virtual ~PawnTest() {
    }

    virtual void SetUp() {
        p = std::make_shared<Pawn>(WHITE);
        p2 = std::make_shared<Pawn>(BLACK);
    }

    virtual void TearDown() {

    }
};




TEST_F(PawnTest, ConstructionTest) {
    //given

    //when

    //then
    ASSERT_EQ(p->getColour(),WHITE);
    ASSERT_EQ(p2->getColour(),BLACK);
}

TEST(PawnTest, MovingToBlankSpotTest) {
    //given
    std::shared_ptr<Pawn> p = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(3,3);

    //then
    ASSERT_TRUE(spot->isOccupied());


    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,5);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(5,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(6,4);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,4);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    spot->replacePiece(nullptr);
    spot = board.getSpot(4,4);
    spot->replacePiece(p2);


    ASSERT_TRUE(p2->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(3,4);
    ASSERT_TRUE(p2->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(1,4);
    ASSERT_FALSE(p2->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(5,4);
    ASSERT_FALSE(p2->canMoveTo(board,*spot,*testSpot));
}

TEST(PawnTest,MovingToOccupiedSpotTest) {
    //given
    std::shared_ptr<Pawn> p = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);

    //when
    Board board;
    board.clearBoard();

    std::shared_ptr<BoardSpot> spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(4,4);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(5,4);
    testSpot->replacePiece(p2);
    //then
    ASSERT_TRUE(testSpot->isOccupied());
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot2));
    testSpot->replacePiece(nullptr);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot2));
    testSpot2->replacePiece(p2);


    ASSERT_FALSE(p2->canMoveTo(board,*testSpot2,*spot));
    spot->replacePiece(nullptr);


    ASSERT_TRUE(p2->canMoveTo(board,*testSpot2,*spot));
    testSpot->replacePiece(p);
    ASSERT_FALSE(p2->canMoveTo(board,*testSpot2,*spot));
    ASSERT_FALSE(p2->canMoveTo(board,*testSpot2,*testSpot));


    //takes Test
    testSpot = board.getSpot(4,5);
    testSpot->replacePiece(p2);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
}