#include <gtest/gtest.h>
#include "model/pieces/Rook.h"
#include "model/Board.h"

TEST(RookTest,MoveToBalnkSpotTest) {
    std::shared_ptr<Rook> p = std::make_shared<Rook>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(0,0);

    //then
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,7);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(7,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(0,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,0);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(5,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(3,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
}


TEST(RookTest,MoveThroughOccupiedSpotTest) {
    std::shared_ptr<Rook> p = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Rook> p2 = std::make_shared<Rook>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(4,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(0,4);
    std::shared_ptr<BoardSpot> testSpot2 = board.getSpot(2,4);

    //then

    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2->replacePiece(p2);

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot2));


    testSpot = board.getSpot(4,0);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2 = board.getSpot(4,2);
    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot2));



    testSpot = board.getSpot(4,7);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2 = board.getSpot(4,5);
    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot2));


    testSpot = board.getSpot(7,4);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

    testSpot2 = board.getSpot(5,4);
    testSpot2->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot2));
}