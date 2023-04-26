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
    for (unsigned long i = 2; i < 7; i++) {
        for (unsigned long j = 0; j < 8; j++)
            board[i][j] = PositionFactory::createBlankPosition(int(i),int(j));
    }

}


std::shared_ptr<BoardSpot> Board::getSpot(long unsigned row, long unsigned col) const{
    if (row > 7 || col > 7) return nullptr;
    return board[row][col];
}

void Board::initializeOccupiedSpots() {
    initializeOneSideSpots(true);
    initializeOneSideSpots(false);
}

void Board::initializeOneSideSpots(bool whiteSide) {
    unsigned long x = 0;
    if (!whiteSide) x = 7;
    board[x][0] = PositionFactory::createRookPosition((int)x,0);
    board[x][1] = PositionFactory::createKnightPosition((int)x,1);
    board[x][2] = PositionFactory::createBishopPosition((int)x,2);
    board[x][3] = PositionFactory::createQueenPosition((int)x,3);
    board[x][4] = PositionFactory::createKingPosition((int)x,4);
    board[x][5] = PositionFactory::createBishopPosition((int)x,5);
    board[x][6] = PositionFactory::createKnightPosition((int)x,6);
    board[x][7] = PositionFactory::createRookPosition((int)x,7);

    if (x == 0) x++;
    else x--;

    for (unsigned long i = 0; i < 8; i++) {
        board[x][i] = PositionFactory::createRookPosition((int)x,(int)i);
    }


}
