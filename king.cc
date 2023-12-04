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
    
}


vector<Coordinate> King::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // to do
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

bool King::isChecked(ChessPiece* board[8][8]) const {
    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && i != row && j != col) {
                for (Coordinate move: board[i][j]->possibleMoves) {
                    if (location == move) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

vector<Coordinate> King::getAllCheckMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> checkMoves;
    // can't check cause it will check itself
    return checkMoves;
}
