#include <gtest/gtest.h>
#include "model/PromotionMove.h"
#include "model/pieces/Pawn.h"
#include "model/Board.h"
#include "model/pieces/Rook.h"
#include "model/pieces/Queen.h"
#include "model/pieces/Knight.h"
#include "model/pieces/Bishop.h"

TEST(PromotionTest, MakeAndRevertPiecesTest) {
    //given
    std::shared_ptr<Piece> testPawn1 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Piece> testPawn2 = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Piece> testWhiteRook = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Piece> testBlackRook = std::make_shared<Rook>(BLACK);
    std::shared_ptr<Piece> testQueen = std::make_shared<Queen>(BLACK);
    std::shared_ptr<Piece> testKnight = std::make_shared<Knight>(BLACK);
    std::shared_ptr<Piece> testBishop = std::make_shared<Bishop>(BLACK);
    std::shared_ptr<Piece> testKing= std::make_shared<King>(BLACK);
    Board board;
    board.clearBoard();
    //when
    std::shared_ptr<BoardSpot> promotionSpot = board.getSpot(0, 0);
    promotionSpot->replacePiece(testPawn1);
    PromotionMove move(promotionSpot, testPawn2);
    //then
    EXPECT_FALSE(move.revertIfWasMade(board));

    EXPECT_FALSE(move.makeIfIsLegal(board));

    move = PromotionMove(promotionSpot, testWhiteRook);
    EXPECT_FALSE(move.makeIfIsLegal(board));

    move = PromotionMove(promotionSpot, testKing);
    EXPECT_FALSE(move.makeIfIsLegal(board));

    move = PromotionMove(promotionSpot, testBlackRook);
    EXPECT_TRUE(move.makeIfIsLegal(board));
    move.revertIfWasMade(board);

    move = PromotionMove(promotionSpot, testQueen);
    EXPECT_TRUE(move.makeIfIsLegal(board));
    move.revertIfWasMade(board);

    move = PromotionMove(promotionSpot, testBishop);
    EXPECT_TRUE(move.makeIfIsLegal(board));
    move.revertIfWasMade(board);

    move = PromotionMove(promotionSpot, testKnight);
    EXPECT_TRUE(move.makeIfIsLegal(board));
    EXPECT_FALSE(move.makeIfIsLegal(board));
    move.revertIfWasMade(board);

    promotionSpot->replacePiece(nullptr);
    EXPECT_FALSE(move.makeIfIsLegal(board));
}

TEST(PromotionTest, MakeAndRevertSpotsTest) {
    //given
    std::shared_ptr<Piece> BlackPawn = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Piece> WhitePawn = std::make_shared<Pawn>(WHITE);
    std::shared_ptr<Piece> WhiteRook = std::make_shared<Rook>(WHITE);
    std::shared_ptr<Piece> BlackRook = std::make_shared<Rook>(BLACK);
    Board board;
    board.clearBoard();
    //when
    std::shared_ptr<BoardSpot> promotionSpot = board.getSpot(0, 0);
    promotionSpot->replacePiece(WhitePawn);
    PromotionMove move(promotionSpot, WhiteRook);
    //then
    EXPECT_FALSE(move.makeIfIsLegal(board));

    promotionSpot->replacePiece(BlackPawn);
    move = PromotionMove(promotionSpot, BlackRook);
    EXPECT_TRUE(move.makeIfIsLegal(board));
    move.revertIfWasMade(board);

    promotionSpot = board.getSpot(7, 7);
    promotionSpot->replacePiece(BlackPawn);
    move = PromotionMove(promotionSpot, BlackRook);
    EXPECT_FALSE(move.makeIfIsLegal(board));

    promotionSpot->replacePiece(WhitePawn);
    move = PromotionMove(promotionSpot, WhiteRook);
    EXPECT_TRUE(move.makeIfIsLegal(board));
}