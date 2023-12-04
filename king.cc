// king.cc

#include "king.h"
#include <iostream>

King::King(Coordinate pos, string white)
    : ChessPiece(pos, white, "K") {  // Initialize hasMoved to false
    // You can add additional initialization for the King if needed
    checked = false;
}

void King::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction
    vector<pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},             {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : kingMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (board[newRow][newCol] == nullptr || board[newRow][newCol]->getColour() != getColour())) {
            possibleMoves.push_back({newRow, newCol});
        }
    }



    
    
    if (!moved()) {
        if (col == 4 && board[row][0] != nullptr && board[row][0]->getPiece() == PieceType::R && board[row][0]->getColour() == getColour()
        && !board[row][0]->moved() && board[row][col - 1] == nullptr && board[row][col - 2] == nullptr)
        {
            possibleMoves.push_back({row, col - 2});
        }

        if (col == 4 && board[row][7] != nullptr && board[row][7]->getPiece() == PieceType::R && board[row][7]->getColour() == getColour()
        && !board[row][7]->moved() && board[row][col + 1] == nullptr && board[row][col + 2] == nullptr) {
            possibleMoves.push_back({row, col + 2});
        }
    }

    for (const auto& coord : possibleMoves) {
        if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
            evadeMoves.push_back(coord);
        }
    }
    
}

bool King::isChecked(ChessPiece* board[8][8]) {
    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && i != row && j != col) {

                cerr << "found piece validating" << endl;
                for (const Coordinate &move: board[i][j]->possibleMoves) {
                    cerr << board[i][j]->getCharType() << " ...." << move << endl;
                    if (location == move) {
                        cerr << "location found equal" << endl;
                        //getBlockPlaces(board[i][j]->location, board);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void King::getAllCheckMoves(ChessPiece* board[8][8]) {
    checkMoves.clear();
}

//void getBlockPlaces(Coordinate attacker, ChessPiece* board[8][8]) {

