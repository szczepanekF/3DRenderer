#include <gtest/gtest.h>
#include "model/Move.h"
#include "model/Board.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Bishop.h"

class MoveTest : public testing::Test {

protected:

    Board board;
    std::shared_ptr<BoardSpot> fromSpotTest;
    std::shared_ptr<BoardSpot> toSpotTest;
    std::shared_ptr<Move> move;
    std::shared_ptr<Piece> whiteKing = std::make_shared<King>(WHITE);
    std::shared_ptr<Piece> blackKing = std::make_shared<King>(BLACK);

    MoveTest() {}

    virtual ~MoveTest() {

    }

    virtual void SetUp() {
        board.clearBoard();
        board.getSpot(0,4)->replacePiece(whiteKing);
        board.getSpot(7,4)->replacePiece(blackKing);
    }

    virtual void TearDown() {

    }
};

TEST_F(MoveTest, CanBeMadeTest) {

    //given
    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
    toSpotTest = board.getSpot(0,0);
    fromSpotTest = board.getSpot(1,1);
    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
    Move testMove(toSpotTest,fromSpotTest);
    //when
    EXPECT_FALSE(move->canBeMade(board));
    EXPECT_FALSE(testMove.canBeMade(board));
    fromSpotTest->replacePiece(testPawn1);
    EXPECT_FALSE(move->canBeMade(board));
    EXPECT_FALSE(testMove.canBeMade(board));

    toSpotTest->replacePiece(testPawn2);
    EXPECT_TRUE(move->canBeMade(board));
    EXPECT_TRUE(testMove.canBeMade(board));

}


TEST_F(MoveTest, ShouldNotBeAbleToBeMadeTest) {

    //given

    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
    toSpotTest = board.getSpot(2,5);
    fromSpotTest = board.getSpot(1,5);
    fromSpotTest->replacePiece(testPawn);
    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
    //when
    EXPECT_TRUE(move->canBeMade(board));
    board.getSpot(3,7)->replacePiece(testBishop);
    EXPECT_FALSE(move->canBeMade(board));
}

//
//TEST_F(MoveTest, ShouldBeAbleToCastleTest) {
//
//    //given
//
//    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>(WHITE);
//    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
//    toSpotTest = board.getSpot(2,5);
//    fromSpotTest = board.getSpot(1,5);
//    fromSpotTest->replacePiece(testPawn);
//    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
//    //when
//    EXPECT_TRUE(move->canBeMade(board));
//    board.getSpot(3,7)->replacePiece(testBishop);
//    EXPECT_FALSE(move->canBeMade(board));
//}
//
//TEST_F(MoveTest, ShouldNotBeAbleToCastleTest) {
//
//    //given
//
//    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>(WHITE);
//    std::shared_ptr<Bishop> testBishop = std::make_shared<Bishop>(BLACK);
//    toSpotTest = board.getSpot(2,5);
//    fromSpotTest = board.getSpot(1,5);
//    fromSpotTest->replacePiece(testPawn);
//    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
//    //when
//    EXPECT_TRUE(move->canBeMade(board));
//    board.getSpot(3,7)->replacePiece(testBishop);
//    EXPECT_FALSE(move->canBeMade(board));
//}
//
//TEST_F(MoveTest, MakeMoveTest) {
//
//    //given
//    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
//    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(BLACK);
//    toSpotTest = std::make_shared<BoardSpot>(0, 0, testPawn1);
//    fromSpotTest = std::make_shared<BoardSpot>(0, 0, testPawn2);
//    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
//    //when
//
//}
//
//
//TEST_F(MoveTest, RevertMoveTest) {
//
//    //given
//    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
//    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(BLACK);
//    toSpotTest = std::make_shared<BoardSpot>(0, 0, testPawn1);
//    fromSpotTest = std::make_shared<BoardSpot>(0, 0, testPawn2);
//    move = std::make_shared<Move>(fromSpotTest,toSpotTest);
//    //when
//
//}