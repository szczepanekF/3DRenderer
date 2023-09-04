#include <gtest/gtest.h>
#include "model/pieces/King.h"
#include "model/BoardSpot.h"
#include "model/Board.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Rook.h"


class KingTest : public ::testing::Test {

protected:
    std::shared_ptr<King> king;
    Board board;
    std::shared_ptr<BoardSpot> spot;
    std::shared_ptr<BoardSpot> testSpot;


    KingTest() {
    }

    virtual ~KingTest() {
    }

    virtual void SetUp() {
        king = std::make_shared<King>(WHITE);
        board.clearBoard();
    }

    virtual void TearDown() {

    }
};


TEST_F(KingTest, MoveToBlankSpotTest) {
    //given

    //when



    spot = board.getSpot(3, 4);
    spot->replacePiece(king);

    testSpot = board.getSpot(1, 3);

    //then
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(5, 7);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 3);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(3, 3);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 3);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 4);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 4);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(2, 5);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(3, 5);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(4, 5);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));


}

TEST_F(KingTest, MoveToOccupiedSpotTest) {
    //given
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(WHITE);

    //when

    spot = board.getSpot(3, 4);
    spot->replacePiece(king);

    testSpot = board.getSpot(3, 3);

    //then
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    testSpot->replacePiece(p2);

    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
}


TEST_F(KingTest, CastleThroguhOtherPiecesTest) {
    //given
    std::shared_ptr<Rook> rook = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);
    //when

    spot = board.getSpot(0, 4);
    spot->replacePiece(king);
    testSpot = board.getSpot(0, 7);
    //then



    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    testSpot->replacePiece(rook);
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(rook);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(0, 1)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(0, 1)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(0, 2)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(0, 2)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(0, 3)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(0, 7);

    board.getSpot(0, 3)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(0, 5)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(0, 5)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(0, 6)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));


}

TEST_F(KingTest, CastlingOnCheckTest) {
    //given
    std::shared_ptr<Rook> rook = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);
    //when

    spot = board.getSpot(0, 4);
    spot->replacePiece(king);
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(rook);

    //then

    //KING IS ON CHECK
    board.getSpot(1, 5)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(rook);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(1, 5)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
}

TEST_F(KingTest, CastligThroughAttackedSpotTest) {

    //given
    std::shared_ptr<Rook> rook = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Pawn> p2 = std::make_shared<Pawn>(BLACK);
    //when

    spot = board.getSpot(0, 4);
    spot->replacePiece(king);
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(rook);

    //then
    //KING WILL BE ON CHECK WHILE CASTLING
    board.getSpot(1, 0)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 0)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(1, 1)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 1)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 2)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(0, 7);
    testSpot->replacePiece(rook);

    board.getSpot(1, 2)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 6)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 6)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    board.getSpot(1, 7)->replacePiece(p2);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    board.getSpot(1, 7)->replacePiece(nullptr);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));
}

TEST_F(KingTest, CastlingToMovedRook) {
    //given
    std::shared_ptr<Rook> MovedRook = std::make_shared<Rook>(WHITE);
    MovedRook->move();
    std::shared_ptr<Rook> NotMovedRook = std::make_shared<Rook>(WHITE);

    //when

    spot = board.getSpot(0, 4);
    spot->replacePiece(king);
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(MovedRook);

    //then
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    testSpot->replacePiece(NotMovedRook);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

}

TEST_F(KingTest, CastlingToEnemyRook) {
    //given
    std::shared_ptr<Rook> WhiteRook = std::make_shared<Rook>(WHITE);

    std::shared_ptr<Rook> BlackRook = std::make_shared<Rook>(BLACK);

    //when

    spot = board.getSpot(0, 4);
    spot->replacePiece(king);
    testSpot = board.getSpot(0, 0);
    testSpot->replacePiece(BlackRook);

    //then
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    testSpot->replacePiece(WhiteRook);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

    testSpot = board.getSpot(0,7);

    testSpot->replacePiece(BlackRook);
    EXPECT_FALSE(king->canMoveTo(board, *spot, *testSpot));
    testSpot->replacePiece(WhiteRook);
    EXPECT_TRUE(king->canMoveTo(board, *spot, *testSpot));

}