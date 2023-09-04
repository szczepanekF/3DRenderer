#include <gtest/gtest.h>
#include "model/BoardSpot.h"
#include "model/pieces/King.h"
#include "model/pieces/Pawn.h"

class BoardSpotTest : public ::testing::Test {
public:
    BoardSpot testSpot = BoardSpot(0, 4, nullptr);

protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }


};


TEST_F(BoardSpotTest, ConstructionTest) {
    //given


    BoardSpot occupiedSpot(3, 1, std::make_shared<Pawn>());

    //when

    //then
    EXPECT_EQ(testSpot.getRow(), 0);
    EXPECT_EQ(testSpot.getColumn(), 4);
    EXPECT_EQ(occupiedSpot.getRow(), 3);
    EXPECT_EQ(occupiedSpot.getColumn(), 1);

    EXPECT_FALSE(testSpot.isOccupied());
    EXPECT_TRUE(occupiedSpot.isOccupied());

}

TEST_F(BoardSpotTest, GetPieceColour) {
    //given

    //when

    BoardSpot whitePieceSpot(0, 0, std::make_shared<Pawn>(WHITE));
    BoardSpot blackPieceSpot(0, 0, std::make_shared<Pawn>(BLACK));



    //then
    EXPECT_EQ(testSpot.getPieceColour(), NO_COLOUR);
    EXPECT_EQ(whitePieceSpot.getPieceColour(), WHITE);
    EXPECT_EQ(blackPieceSpot.getPieceColour(), BLACK);
    EXPECT_EQ(testSpot.getPieceOppositeColour(), NO_COLOUR);
    EXPECT_EQ(whitePieceSpot.getPieceOppositeColour(), BLACK);
    EXPECT_EQ(blackPieceSpot.getPieceOppositeColour(), WHITE);
}

TEST_F(BoardSpotTest, GetPieceTest) {
    //given
    //when
    std::shared_ptr<Pawn> testPawn = std::make_shared<Pawn>();
    BoardSpot occupiedSpot(0, 0, testPawn);
    //then
    EXPECT_EQ(occupiedSpot.getPiece(), testPawn);


}

TEST_F(BoardSpotTest, ReplacePieceTest) {
    //given

    //when
    std::shared_ptr<Piece> piece = std::make_unique<King>();
    EXPECT_EQ(testSpot.replacePiece(piece), nullptr);

    //then
    EXPECT_EQ(testSpot.getPiece(), piece);
    EXPECT_EQ(testSpot.replacePiece(nullptr), piece);
}

