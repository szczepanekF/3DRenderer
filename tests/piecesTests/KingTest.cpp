#include <gtest/gtest.h>
#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Pawn.h"


class KingTest : public ::testing::Test {

protected:
    std::shared_ptr<King> p;
    Board board;
    std::shared_ptr<BoardSpot> spot;



    KingTest() {
    }

    virtual ~KingTest() {
    }

    virtual void SetUp() {
        p  = std::make_shared<King>(WHITE);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};


TEST_F(KingTest,MoveToBlankSpotTest) {
    //given

    //when



    spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(1,3);

    //then
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(5,7);
    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,3);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(3,3);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,3);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,4);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,4);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,5);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(3,5);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,5);
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));


}

TEST_F(KingTest,MoveToOccupiedSpotTest) {
    //given
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(WHITE);

    //when

    spot = board.getSpot(3, 4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(3, 3);

    //then
    EXPECT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot->replacePiece(p2);

    EXPECT_FALSE(p->canMoveTo(board,*spot,*testSpot));
}