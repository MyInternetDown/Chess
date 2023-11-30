// rook.cc

#include "rook.h"

Rook::Rook(string pos, string white)
    : ChessPiece(pos, white, "R"), hasMoved(false) {  // Initialize hasMoved to false
    // You can add additional initialization for the Rook if needed
}

vector<Coordinate> Rook::getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const {
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

bool Rook::moved() {
    return hasMoved;
}
