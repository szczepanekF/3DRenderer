#include <gtest/gtest.h>
#include "model/pieces/Knight.h"
#include "model/Board.h"

TEST(KnightTest,MoveToBlankSpotTest) {
    //given
    std::shared_ptr<Knight> p = std::make_shared<Knight>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(3,3);

    //then

    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,3);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,4);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

    testSpot = board.getSpot(1,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(1,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,2);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(2,6);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));


    testSpot = board.getSpot(5,3);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(5,5);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,2);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot = board.getSpot(4,6);
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));

}
TEST(KnightTest, MoveToOccupiedSpotTest) {
    //given
    std::shared_ptr<Knight> p = std::make_shared<Knight>(WHITE);
    std::shared_ptr<Knight> p2 = std::make_shared<Knight>(WHITE);

    //when
    Board board;
    board.clearBoard();


    std::shared_ptr<BoardSpot> spot = board.getSpot(3,4);
    spot->replacePiece(p);

    std::shared_ptr<BoardSpot> testSpot = board.getSpot(1,3);

    //then
    ASSERT_TRUE(p->canMoveTo(board,*spot,*testSpot));
    testSpot->replacePiece(p2);
    ASSERT_FALSE(p->canMoveTo(board,*spot,*testSpot));

}