#include <gtest/gtest.h>
#include "model/RegularMove.h"
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
    std::shared_ptr<RegularMove> move;
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
    RegularMove testMove1(fromSpotTest, toSpotTest);
    RegularMove testMove2(toSpotTest, fromSpotTest);
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
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

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
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

    //then
    EXPECT_TRUE(move->isLegal(board));
    board.getSpot(7, 0)->replacePiece(testQueen);

    EXPECT_TRUE(move->isLegal(board));

    toSpotTest = board.getSpot(0, 1);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);
    EXPECT_FALSE(move->isLegal(board));

    toSpotTest = board.getSpot(0, 2);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);
    EXPECT_TRUE(move->isLegal(board));

    toSpotTest = board.getSpot(0, 3);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);
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
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

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
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

    //then
    EXPECT_FALSE(move->isLegal(board));
    testRook->undoMove();
    EXPECT_TRUE(move->isLegal(board));
    whiteKing->move();
    EXPECT_FALSE(move->isLegal(board));
}

TEST_F(MoveTest, MakeIfIsLegalAndRevertIfWasMadeTest) {
    //given
    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(WHITE);
    fromSpotTest = board.getSpot(1, 1);
    toSpotTest = board.getSpot(0, 0);

    //when
    fromSpotTest->replacePiece(testPawn1);
    toSpotTest->replacePiece(testPawn2);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

    //then

    ASSERT_FALSE(move->revertIfWasMade(board));
    ASSERT_TRUE(move->makeIfIsLegal(board));

    EXPECT_TRUE(testPawn1->wasMoved());

    ASSERT_FALSE(move->makeIfIsLegal(board));
    ASSERT_TRUE(move->revertIfWasMade(board));

    toSpotTest->replacePiece(nullptr);
    EXPECT_FALSE(move->makeIfIsLegal(board));
    EXPECT_FALSE(testPawn1->wasMoved());
}


TEST_F(MoveTest, MakeAndRevertMoveTest) {
    //given
    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(WHITE);

    fromSpotTest = board.getSpot(1, 1);
    toSpotTest = board.getSpot(0, 0);

    //when
    fromSpotTest->replacePiece(testPawn1);
    toSpotTest->replacePiece(testPawn2);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);
    move->makeIfIsLegal(board);

    //then
    EXPECT_EQ(fromSpotTest->getPiece(), nullptr);
    EXPECT_EQ(toSpotTest->getPiece(), testPawn1);
    EXPECT_TRUE(testPawn1->wasMoved());

    move->revertIfWasMade(board);

    EXPECT_FALSE(testPawn1->wasMoved());

    EXPECT_EQ(fromSpotTest->getPiece(), testPawn1);
    EXPECT_EQ(toSpotTest->getPiece(), testPawn2);
}



TEST_F(MoveTest, CastlingPerformAndUnperformTest) {
    //given
    std::shared_ptr<Rook> rook = std::make_shared<Rook>(WHITE);
    fromSpotTest = board.getSpot(0, 4);
    std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(fromSpotTest->getPiece());
    toSpotTest = board.getSpot(0, 0);
    toSpotTest->replacePiece(rook);

    //when
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);
    std::shared_ptr<BoardSpot> newKingSpot = board.getSpot(0, 2);
    std::shared_ptr<BoardSpot> newRookSpot = board.getSpot(0, 3);
    move->makeIfIsLegal(board);

    //then

    EXPECT_TRUE(king->wasMoved());
    EXPECT_TRUE(rook->wasMoved());

    EXPECT_NE(king, fromSpotTest->getPiece());
    EXPECT_NE(rook, toSpotTest->getPiece());
    EXPECT_EQ(king, newKingSpot->getPiece());
    EXPECT_EQ(rook, newRookSpot->getPiece());

    move->revertIfWasMade(board);
    EXPECT_FALSE(king->wasMoved());
    EXPECT_FALSE(rook->wasMoved());

    EXPECT_NE(king, newKingSpot->getPiece());
    EXPECT_NE(rook, newRookSpot->getPiece());
    EXPECT_EQ(king, fromSpotTest->getPiece());
    EXPECT_EQ(rook, toSpotTest->getPiece());

    std::shared_ptr<BoardSpot> endSpot = board.getSpot(0, 2);
    move = std::make_shared<RegularMove>(fromSpotTest, endSpot);

    move->makeIfIsLegal(board);
    EXPECT_TRUE(king->wasMoved());
    EXPECT_TRUE(rook->wasMoved());

    EXPECT_NE(king, fromSpotTest->getPiece());
    EXPECT_NE(rook, toSpotTest->getPiece());
    EXPECT_EQ(king, newKingSpot->getPiece());
    EXPECT_EQ(rook, newRookSpot->getPiece());

    move->revertIfWasMade(board);
    EXPECT_FALSE(king->wasMoved());
    EXPECT_FALSE(rook->wasMoved());

    EXPECT_NE(king, newKingSpot->getPiece());
    EXPECT_NE(rook, newRookSpot->getPiece());
    EXPECT_EQ(king, fromSpotTest->getPiece());
    EXPECT_EQ(rook, toSpotTest->getPiece());
}



TEST_F(MoveTest, UpdateEnPassantTest) {
    //given

    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>(WHITE);
    fromSpotTest = board.getSpot(0, 0);
    toSpotTest = board.getSpot(2, 0);

    //when
    fromSpotTest->replacePiece(testPawn);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

    //then
    ASSERT_TRUE(move->makeIfIsLegal(board));

    EXPECT_EQ(board.getEnPassantCol(), toSpotTest->getColumn());

    ASSERT_TRUE(move->revertIfWasMade(board));

    EXPECT_EQ(board.getEnPassantCol(), -1);
}


TEST_F(MoveTest, EnPassantTest) {
    //given

    std::shared_ptr<Pawn> testPawn1 = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Pawn> testPawn2 = std::make_shared<Pawn>(BLACK);
    fromSpotTest = board.getSpot(4, 0);
    toSpotTest = board.getSpot(5, 1);

    //when
    fromSpotTest->replacePiece(testPawn1);
    move = std::make_shared<RegularMove>(fromSpotTest, toSpotTest);

    //then
    EXPECT_FALSE(move->makeIfIsLegal(board));

    board.setEnPassantCol(1);

    EXPECT_FALSE(move->makeIfIsLegal(board));

    board.getSpot(4,1)->replacePiece(testPawn2);

    EXPECT_TRUE(move->makeIfIsLegal(board));

    board.setEnPassantCol(-1);

    EXPECT_FALSE(move->makeIfIsLegal(board));
}
