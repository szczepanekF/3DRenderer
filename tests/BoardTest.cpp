#include <gtest/gtest.h>
#include "model/Board.h"

TEST(BoardTest, ConstructionTest) {
    //given
    Board b;
    //when

    //then
    ASSERT_EQ(b.getSpot(-1,0),nullptr);
    ASSERT_EQ(b.getSpot(0,-1),nullptr);
    ASSERT_EQ(b.getSpot(8,0),nullptr);
    ASSERT_EQ(b.getSpot(0,8),nullptr);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_NE(b.getSpot(i,j),nullptr);
        }
    }
}

TEST(BoardTest, GetPiecesOfColourTest) {
    //given
    Board b;
    //when

    //then

    ASSERT_EQ(b.getPiecesOfColour(BLACK).size(),16);
    ASSERT_EQ(b.getPiecesOfColour(WHITE).size(),16);

}

TEST(BoardTest, GetKingOfColourTest) {
    //given
    Board b;
    //when
    std::shared_ptr<Piece> realWhiteKing = b.getSpot(0,4)->getPiece();
    std::shared_ptr<Piece> realBlackKing = b.getSpot(7,4)->getPiece();

    std::shared_ptr<King> testWhiteKing = b.getKingOfColour(WHITE);
    std::shared_ptr<King> testBlackKing = b.getKingOfColour(BLACK);
    //then

    ASSERT_EQ(realWhiteKing.get(),testWhiteKing.get());
    ASSERT_EQ(realBlackKing.get(),testBlackKing.get());

    ASSERT_NE(realWhiteKing.get(),testBlackKing.get());
    ASSERT_NE(realBlackKing.get(),testWhiteKing.get());

}

TEST(BoardTest,ClearBoardTest) {
    //given
    Board b;
    //when
    b.clearBoard();

    //then
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_EQ(b.getSpot(i,j)->getPiece(),nullptr);
        }
    }

}
