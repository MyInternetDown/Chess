// rook.cc

#include "rook.h"

Rook::Rook(string pos, string white)
    : ChessPiece(pos, white, "R"){  // Initialize hasMoved to false
    // You can add additional initialization for the Rook if needed
}

vector<Coordinate> Rook::getAllMoves(const Coordinate position, const ChessPiece ***board) {
    vector<Coordinate> moves;

    const int row = position.getRow();
    const int col = position.getCol();

    // Rook moves vertically
    for (int newRow = 0; newRow < 8; ++newRow) {
        if (newRow != row) {
            moves.push_back(Coordinate(newRow, col));
        }
    }

    // Rook moves horizontally
    for (int newCol = 0; newCol < 8; ++newCol) {
        if (newCol != col) {
            moves.push_back(Coordinate(row, newCol));
        }
    }

    return moves;
}

vector<Coordinate> Rook::getAllAttackMoves(const vector<Coordinate> moves, const ChessPiece ***board) const {
    // Implement the Rook's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : moves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

