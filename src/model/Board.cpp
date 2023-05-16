//
// Created by szczepan on 25.04.23.
//

#include "model/Board.h"
#include "model/PositionFactory.h"

Board::Board() {
   initBoard();
}

void Board::initBoard() {

    initializeOccupiedSpots();
    for (int i = 2; i < 7; i++) {
        for (int j = 0; j < 8; j++)
            board[i][j] = PositionFactory::createBlankPosition(i,j);
    }

}


std::shared_ptr<BoardSpot> Board::getSpot(unsigned int row, unsigned int col) const{
    if (row > 7 || col > 7) return nullptr;
    return board[row][col];
}

void Board::initializeOccupiedSpots() {
    initializeOneSideSpots(WHITE);
    initializeOneSideSpots(BLACK);
}

void Board::initializeOneSideSpots(Colour side) {
    int x;
    if (side == BLACK) {
        x = 7;
        PositionFactory::setBlackSide();
    } else {
        x = 0;
        PositionFactory::setWhiteSide();
    }
    board[x][0] = PositionFactory::createRookPosition(x,0);
    board[x][1] = PositionFactory::createKnightPosition(x,1);
    board[x][2] = PositionFactory::createBishopPosition(x,2);
    board[x][3] = PositionFactory::createQueenPosition(x,3);
    board[x][4] = PositionFactory::createKingPosition(x,4);
    board[x][5] = PositionFactory::createBishopPosition(x,5);
    board[x][6] = PositionFactory::createKnightPosition(x,6);
    board[x][7] = PositionFactory::createRookPosition(x,7);

    if (x == 0) x++;
    else x--;

    for (int i = 0; i < 8; i++) {
        board[x][i] = PositionFactory::createPawnPosition(x, i);
    }


}
