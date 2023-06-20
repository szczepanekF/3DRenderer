#include <gtest/gtest.h>
#include "model/pieces/Queen.h"
#include "model/Board.h"

TEST(QueenTest,MovingTest) {
    //given
    std::shared_ptr<Queen> p = std::make_shared<Queen>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(2,3);

    //then

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(6,5);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(0,0);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,1);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(1,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,0);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(0,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
}


TEST(QueenTest,MovingThroughOccupiedSpotsTest) {
    //given
    std::shared_ptr<Queen> p = std::make_shared<Queen>(WHITE);
    std::shared_ptr<Queen> p2 = std::make_shared<Queen>(WHITE);
    //when
    Board board;
    board.clearBoard();

    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(0,0);

    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(3,3);

//    then
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    testSpot2 = board.getSpot(5,5);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(7,1);
    testSpot2 = board.getSpot(5,3);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(1,7);
    testSpot2 = board.getSpot(3,5);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(4,7);
    testSpot2 = board.getSpot(4,5);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,4);
    testSpot2 = board.getSpot(6,4);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(4,0);
    testSpot2 = board.getSpot(4,2);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(0,4);
    testSpot2 = board.getSpot(2,4);

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));


}

