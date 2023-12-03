// pawn.cc

#include "pawn.h"

Pawn::Pawn(string pos, string white)
    : ChessPiece(pos, white, "P") {  // Initialize hasMoved to false
    // You can add additional initialization for the Pawn if needed
}

vector<Coordinate> Pawn::getAllMoves(const Coordinate position, const ChessPiece ***board) {
    vector<Coordinate> moves;

    const int row = position.getRow();
    const int col = position.getCol();

    int forwardDirection = (getColour() == Colour::White) ? -1 : 1;

    // Pawn moves forward
    int newRow = row + forwardDirection;
    if (newRow >= 0 && newRow < 8 && board[newRow][col] == nullptr) {
        moves.push_back(Coordinate(newRow, col));

        // Pawn's double move from starting position
        if (!hasMoved) {
            newRow += forwardDirection;
            if (newRow >= 0 && newRow < 8 && board[newRow][col]==nullptr) {
                moves.push_back(Coordinate(newRow, col));
            }
        }
    }

    // Pawn attacks diagonally
    for (int colOffset : {-1, 1}) {
        int newCol = col + colOffset;
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            !(board[newRow][newCol] == nullptr) && board[newRow][newCol]->getColour() != getColour()) {
            moves.push_back(Coordinate(newRow, newCol));
        }
    }
    return moves;
}

