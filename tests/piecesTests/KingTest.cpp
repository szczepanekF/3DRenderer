#include <gtest/gtest.h>
#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Pawn.h"


TEST(KingTest, ConstructionTest) {
    //given
//    std::shared_ptr<Piece> king = std::shared_ptr<King>();
    BoardSpot position(0, 1, nullptr);

    //when
    ASSERT_EQ(position.getRow(),0);
    //then
    ASSERT_EQ(position.getRow(),0);


}

TEST(KingTest,MoveToBlankSpotTest) {
    std::shared_ptr<King> p = std::make_shared<King>(WHITE);


    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(1,3);

    //then
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(5,7);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(3,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(2,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(3,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));


}

TEST(KingTest,MoveToOccupiedSpotTest) {
    std::shared_ptr<King> p = std::make_shared<King>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(3, 4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(3, 3);

    //then
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot->replacePiece(p2);

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
}