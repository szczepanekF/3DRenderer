#include <gtest/gtest.h>
#include "model/Board.h"
#include "model/pieces/Pawn.h"
#include "model/pieces/Queen.h"

class BoardTest : public ::testing::Test {
public:
    Board b;
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};


TEST_F(BoardTest, ConstructionTest) {
    //given

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

    EXPECT_EQ(b.getEnPassantCol(), -1);
}

TEST_F(BoardTest, GetPiecesOfColourTestShouldEqual16) {
    //given

    //when

    //then
    std::vector<std::shared_ptr<BoardSpot>> spots = b.getPiecesOfColour(BLACK);
    EXPECT_EQ(spots.size(), 16);
    for (auto spot: spots) {
        EXPECT_EQ(spot->getPieceColour(), BLACK);
    }
    spots = b.getPiecesOfColour(WHITE);
    EXPECT_EQ(spots.size(), 16);

    for (auto spot: spots) {
        EXPECT_EQ(spot->getPieceColour(), WHITE);
    }

}

TEST_F(BoardTest, GetPiecesOfColourTestShouldEqual0) {
    //given

    //when
    b.clearBoard();
    //then

    EXPECT_EQ(b.getPiecesOfColour(BLACK).size(), 0);
    EXPECT_EQ(b.getPiecesOfColour(WHITE).size(), 0);

}


TEST_F(BoardTest, GetKingOfColourTest) {
    //given

    //when
    std::shared_ptr<Piece> realWhiteKing = b.getSpot(0, 4)->getPiece();
    std::shared_ptr<Piece> realBlackKing = b.getSpot(7, 4)->getPiece();

    std::shared_ptr<King> testWhiteKing = std::dynamic_pointer_cast<King>(
            b.getKingSpotOfColour(WHITE)->getPiece());
    std::shared_ptr<King> testBlackKing = std::dynamic_pointer_cast<King>(
            b.getKingSpotOfColour(BLACK)->getPiece());
    //then

    EXPECT_EQ(realWhiteKing, testWhiteKing);
    EXPECT_EQ(realBlackKing, testBlackKing);

    EXPECT_NE(realWhiteKing, testBlackKing);
    EXPECT_NE(realBlackKing, testWhiteKing);

}

TEST_F(BoardTest, ClearBoardTest) {
    //given

    //when
    b.clearBoard();

    //then
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            EXPECT_EQ(b.getSpot(i, j)->getPiece(), nullptr);
        }
    }

}


TEST_F(BoardTest, IsSpotAttackedTest) {
    //given

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

TEST_F(BoardTest, SetEnPassantColTest) {
    //given & when & then
    b.setEnPassantCol(3);
    EXPECT_EQ(b.getEnPassantCol(), 3);
    b.setEnPassantCol(7);
    EXPECT_EQ(b.getEnPassantCol(), 7);
    b.setEnPassantCol(-1);
    EXPECT_EQ(b.getEnPassantCol(), -1);

    b.setEnPassantCol(-2);
    EXPECT_EQ(b.getEnPassantCol(), -1);
    b.setEnPassantCol(-8);
    EXPECT_EQ(b.getEnPassantCol(), -1);
}