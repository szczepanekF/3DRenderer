#include <gtest/gtest.h>
#include "model/pieces/Bishop.h"
#include "model/Board.h"

TEST(BishopTest,MovingTest) {
    //given
    std::shared_ptr<Bishop> p = std::make_shared<Bishop>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(4,3);

    //then

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(5,4);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(0,0);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(7,1);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(1,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
}

TEST(BishopTest,MovingTroughOccupiedSpotsTest) {
    std::shared_ptr<Bishop> p = std::make_shared<Bishop>(WHITE);
    std::shared_ptr<Bishop> p2 = std::make_shared<Bishop>(WHITE);
    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(7,7);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(6,6);
    //then


    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));



    testSpot = board.getSpot(7,1);
    testSpot2 = board.getSpot(6,2);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

}