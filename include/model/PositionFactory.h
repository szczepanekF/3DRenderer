#pragma once



#include "BoardSpot.h"

class PositionFactory {
public:
    PositionFactory();

    static std::shared_ptr<BoardSpot> createBlankPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createKingPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createPawnPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createBishopPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createKnightPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createRookPosition(int row, int col);
    static std::shared_ptr<BoardSpot> createQueenPosition(int row, int col);

    static void setBlackSide();
    static void setWhiteSide();

private:
    static Colour sideColour;

};

