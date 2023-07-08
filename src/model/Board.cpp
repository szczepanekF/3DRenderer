

#include "model/Board.h"
#include "model/PositionFactory.h"
#include <vector>
#include <iostream>

Board::Board() {
   initBoard();
}

void Board::initBoard() {

    initializeOccupiedSpots();
    initializeEmptySpots();

}

void Board::initializeOccupiedSpots() {
    initializeOneSideSpots(WHITE);
    initializeOneSideSpots(BLACK);
}

void Board::initializeOneSideSpots(Colour side) {
    int x;
    if (side == BLACK) {
        x = BOARD_LENGTH - 1;
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

    for (int i = 0; i < BOARD_LENGTH; i++) {
        board[x][i] = PositionFactory::createPawnPosition(x, i);
    }


}

void Board::initializeEmptySpots() {
    int occupiedRows = 2;

    for (int i = occupiedRows; i < BOARD_LENGTH - occupiedRows; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++)
            board[i][j] = PositionFactory::createBlankPosition(i,j);
    }
}

void Board::clearBoard() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++)
            board[i][j] = PositionFactory::createBlankPosition(i,j);
    }
}


std::shared_ptr<BoardSpot> Board::getSpot(int row, int col) const{
    if (row > 7 || col > 7 || row < 0 || col < 0) return nullptr;
    return board[row][col];
}

std::vector<std::shared_ptr<BoardSpot>> Board::getPiecesOfColour(Colour colour) const {
    std::vector<std::shared_ptr<BoardSpot>> spots;
    unsigned long maxPiecesAmount = BOARD_LENGTH * 2;
    spots.reserve(maxPiecesAmount);
    fillWithSameColour(spots,colour);
    spots.shrink_to_fit();
    return spots;
}

void Board::fillWithSameColour(std::vector<std::shared_ptr<BoardSpot>> &vec, Colour colour) const {
    for (const auto & i : board) {
        for (const auto & j : i) {
            Colour spotColour = j->getPieceColour();
            if (spotColour == colour) {
                vec.emplace_back(j);
            }
        }
    }
}

std::shared_ptr<King> Board::getKingOfColour(Colour colour) const {
    std::vector<std::shared_ptr<BoardSpot>> spots = getPiecesOfColour(colour);

    for (const auto& spot: spots) {
        std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(spot->getPiece());
        if (king != nullptr) {
            return king;
        }
    }

    throw std::logic_error("King of given colour is not on a board - Weird!");

}


bool Board::isSpotAttackedBy(int x, int y, Colour colour) const {
    std::vector<std::shared_ptr<BoardSpot>> spots = getPiecesOfColour(colour);
    std::shared_ptr<BoardSpot> spotToCheck = board[x][y];
    std::shared_ptr<Piece> currPiece;
    for(auto spot: spots) {
        currPiece = spot->getPiece();
        if (currPiece->canTake(*this,*spot,*spotToCheck)) {
            return true;
        }
    }
    return false;
}




