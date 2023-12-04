// pawn.cc

#include "pawn.h"

Pawn::Pawn(Coordinate pos, string white)
    : ChessPiece(pos, white, "P") {  // Initialize hasMoved to false
    // You can add additional initialization for the Pawn if needed
}

void Pawn::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    int forwardDirection = (getColour() == Colour::White) ? 1 : -1;

    // Pawn moves forward
    int newRow = row + forwardDirection;
    if (newRow >= 0 && newRow < 8 && board[newRow][col] == nullptr) {
        possibleMoves.push_back(Coordinate(newRow, col));

        // Pawn's double move from starting position
        if (!hasMoved) {
            newRow += forwardDirection;
            if (newRow >= 0 && newRow < 8 && board[newRow][col]==nullptr) {
                possibleMoves.push_back(Coordinate(newRow, col));
            }
        }
    }

    // Pawn attacks diagonally
    for (int colOffset : {-1, 1}) {
        int newCol = col + colOffset;
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            !(board[newRow][newCol] == nullptr) && board[newRow][newCol]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(newRow, newCol));
        }
    }
}


vector<Coordinate> Pawn::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Queen's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

vector<Coordinate> Pawn::getAllCheckMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> checkMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getPiece() == K) {
            checkMoves.push_back(move);
        }
    }

    return checkMoves;
}

