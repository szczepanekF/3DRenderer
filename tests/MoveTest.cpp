#include <gtest/gtest.h>
#include "model/Move.h"
#include "model/Board.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Bishop.h"
#include "model/pieces/Queen.h"
#include "model/pieces/Rook.h"

class MoveTest : public testing::Test {

protected:

    Board board;
    std::shared_ptr<BoardSpot> fromSpotTest;
    std::shared_ptr<BoardSpot> toSpotTest;
    std::shared_ptr<Move> move;
    std::shared_ptr<MoveSensitivePiece> whiteKing;
    std::shared_ptr<MoveSensitivePiece> blackKing;

    MoveTest() {}

    virtual ~MoveTest() {

    }

    virtual void SetUp() {
        board.clearBoard();
        whiteKing = std::make_shared<King>(WHITE);
        blackKing = std::make_shared<King>(BLACK);
        board.getSpot(0, 4)->replacePiece(whiteKing);
        board.getSpot(7, 4)->replacePiece(blackKing);
    }

    virtual void TearDown() {

    }
};

TEST_F(MoveTest, CanBeMadeTest) {

    //given
    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
    toSpotTest = board.getSpot(0, 0);
    fromSpotTest = board.getSpot(1, 1);

    //when
    Move testMove1(fromSpotTest, toSpotTest);
    Move testMove2(toSpotTest, fromSpotTest);
    //then
    EXPECT_FALSE(testMove1.isLegal(board));
    EXPECT_FALSE(testMove2.isLegal(board));
    fromSpotTest->replacePiece(testPawn1);
    EXPECT_FALSE(testMove1.isLegal(board));
    EXPECT_FALSE(testMove2.isLegal(board));

    toSpotTest->replacePiece(testPawn2);
    EXPECT_TRUE(testMove1.isLegal(board));
    EXPECT_TRUE(testMove2.isLegal(board));

}


TEST_F(MoveTest, ShouldNotBeAbleToBeMadeTest) {
    //given
    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
    toSpotTest = board.getSpot(2, 5);
    fromSpotTest = board.getSpot(1, 5);

    //when
    fromSpotTest->replacePiece(testPawn);
    move = std::make_shared<Move>(fromSpotTest, toSpotTest);

    //then
    EXPECT_TRUE(move->isLegal(board));
    board.getSpot(3, 7)->replacePiece(testBishop);
    EXPECT_FALSE(move->isLegal(board));
}


TEST_F(MoveTest, ShouldBeAbleToCastleTest) {
    //given
    std::shared_ptr<Queen> testQueen = std::make_shared<Queen>(BLACK);
    std::shared_ptr<Rook> testRook = std::make_shared<Rook>(WHITE);

    fromSpotTest = board.getSpot(0, 4);
    toSpotTest = board.getSpot(0, 0);

    //when
    toSpotTest->replacePiece(testRook);
    move = std::make_shared<Move>(fromSpotTest, toSpotTest);

    //then
    EXPECT_TRUE(move->isLegal(board));
    board.getSpot(7, 0)->replacePiece(testQueen);
    EXPECT_TRUE(move->isLegal(board));
}

TEST_F(MoveTest, ShouldNotBeAbleToCastleOnAndThroughCheckTest) {
    //given
    std::shared_ptr<Queen> testQueen = std::make_shared<Queen>(BLACK);
    std::shared_ptr<Rook> testRook = std::make_shared<Rook>(WHITE);

    fromSpotTest = board.getSpot(0, 4);
    toSpotTest = board.getSpot(0, 0);

    //when
    toSpotTest->replacePiece(testRook);
    move = std::make_shared<Move>(fromSpotTest, toSpotTest);

    //then
    EXPECT_TRUE(move->isLegal(board));
    board.getSpot(7, 1)->replacePiece(testQueen);
    EXPECT_FALSE(move->isLegal(board));

    board.getSpot(7, 1)->replacePiece(nullptr);
    board.getSpot(7, 2)->replacePiece(testQueen);
    EXPECT_FALSE(move->isLegal(board));

    board.getSpot(7, 2)->replacePiece(nullptr);
    board.getSpot(7, 3)->replacePiece(testQueen);
    EXPECT_FALSE(move->isLegal(board));

    board.getSpot(7, 3)->replacePiece(nullptr);
    board.getSpot(7, 4)->replacePiece(testQueen);
    EXPECT_FALSE(move->isLegal(board));
}


TEST_F(MoveTest, ShouldNotBeAbleToCastleAfterMoveTest) {
    //given
    std::shared_ptr<Rook> testRook = std::make_shared<Rook>(WHITE);

    fromSpotTest = board.getSpot(0, 4);
    toSpotTest = board.getSpot(0, 0);

    //when
    toSpotTest->replacePiece(testRook);
    testRook->move();
    move = std::make_shared<Move>(fromSpotTest, toSpotTest);

    //then
    EXPECT_FALSE(move->isLegal(board));
    testRook->undoMove();
    EXPECT_TRUE(move->isLegal(board));
    whiteKing->move();
    EXPECT_FALSE(move->isLegal(board));
}


TEST_F(MoveTest, MakeAndRevertMoveTest) {
    //given
    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(WHITE);
    fromSpotTest = std::make_shared<BoardSpot>(1, 1, testPawn1);
    toSpotTest = std::make_shared<BoardSpot>(0, 0, testPawn2);

    //when
    move = std::make_shared<Move>(fromSpotTest, toSpotTest);
    move->make();

    //then
    EXPECT_EQ(fromSpotTest->getPiece(), nullptr);
    EXPECT_EQ(toSpotTest->getPiece(), testPawn1);
    EXPECT_TRUE(testPawn1->wasMoved());

    move->revert();

    EXPECT_FALSE(testPawn1->wasMoved());

    EXPECT_EQ(fromSpotTest->getPiece(), testPawn1);
    EXPECT_EQ(toSpotTest->getPiece(), testPawn2);

}


