// rook.cc

#include "rook.h"

Rook::Rook(Coordinate pos, string white)
    : ChessPiece(pos, white, "R"){  // Initialize hasMoved to false
    // You can add additional initialization for the Rook if needed
}

void Rook::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    // Rook moves vertically
    for (int newRow = 0; newRow < 8; ++newRow) {
        if (newRow != row) {
            possibleMoves.push_back(Coordinate(newRow, col));
        }
    }


    // Rook moves horizontally
    for (int newCol = 0; newCol < 8; ++newCol) {
        if (newCol != col) {
            possibleMoves.push_back(Coordinate(row, newCol));
        }
    }
}

vector<Coordinate> Rook::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Rook's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

