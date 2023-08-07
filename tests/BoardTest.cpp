#include <gtest/gtest.h>
#include "model/Board.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Queen.h"

TEST(BoardTest, ConstructionTest) {
    //given
    Board b;
    //when

    //then
    EXPECT_EQ(b.getSpot(-1, 0), nullptr);
    EXPECT_EQ(b.getSpot(0, -1), nullptr);
    EXPECT_EQ(b.getSpot(8, 0), nullptr);
    EXPECT_EQ(b.getSpot(0, 8), nullptr);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_NE(b.getSpot(i, j), nullptr);
        }
    }
}

TEST(BoardTest, GetPiecesOfColourTest) {
    //given
    Board b;
    //when

    //then

    EXPECT_EQ(b.getPiecesOfColour(BLACK).size(), 16);
    EXPECT_EQ(b.getPiecesOfColour(WHITE).size(), 16);

}

TEST(BoardTest, GetKingOfColourTest) {
    //given
    Board b;
    //when
    std::shared_ptr<Piece> realWhiteKing = b.getSpot(0, 4)->getPiece();
    std::shared_ptr<Piece> realBlackKing = b.getSpot(7, 4)->getPiece();

    std::shared_ptr<King> testWhiteKing = std::dynamic_pointer_cast<King>(
            b.getKingSpotOfColour(WHITE)->getPiece());
    std::shared_ptr<King> testBlackKing = std::dynamic_pointer_cast<King>(
            b.getKingSpotOfColour(BLACK)->getPiece());
    //then

    EXPECT_EQ(realWhiteKing.get(), testWhiteKing.get());
    EXPECT_EQ(realBlackKing.get(), testBlackKing.get());

    EXPECT_NE(realWhiteKing.get(), testBlackKing.get());
    EXPECT_NE(realBlackKing.get(), testWhiteKing.get());

}

TEST(BoardTest, ClearBoardTest) {
    //given
    Board b;
    //when
    b.clearBoard();

    //then
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(b.getSpot(i, j)->getPiece(), nullptr);
        }
    }

}


TEST(BoardTest, IsSpotAttackedTest) {
    //given
    Board b;
    b.clearBoard();
    std::shared_ptr<Piece> blackP = std::make_shared<Pawn>(BLACK);
    std::shared_ptr<Piece> whiteP = std::make_shared<Queen>(WHITE);
    std::shared_ptr<BoardSpot> blackSpot = b.getSpot(4, 4);
    std::shared_ptr<BoardSpot> whiteSpot = b.getSpot(3, 3);

    //when
    blackSpot->replacePiece(blackP);
    whiteSpot->replacePiece(whiteP);
    //then

    EXPECT_FALSE(b.isSpotAttackedBy(5, 5, BLACK));
    EXPECT_FALSE(b.isSpotAttackedBy(5, 3, BLACK));

    EXPECT_TRUE(b.isSpotAttackedBy(3, 3, BLACK));
    EXPECT_TRUE(b.isSpotAttackedBy(3, 5, BLACK));


    EXPECT_FALSE(b.isSpotAttackedBy(5, 5, WHITE));
    EXPECT_FALSE(b.isSpotAttackedBy(4, 5, WHITE));

    EXPECT_TRUE(b.isSpotAttackedBy(4, 4, WHITE));
    EXPECT_TRUE(b.isSpotAttackedBy(0, 3, WHITE));
    EXPECT_TRUE(b.isSpotAttackedBy(7, 3, WHITE));
    EXPECT_TRUE(b.isSpotAttackedBy(3, 7, WHITE));
    EXPECT_TRUE(b.isSpotAttackedBy(3, 0, WHITE));
    EXPECT_TRUE(b.isSpotAttackedBy(0, 0, WHITE));

}