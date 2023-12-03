// bishop.cc

#include "bishop.h"
#include <iostream>

Bishop::Bishop(Coordinate pos, string white)
    : ChessPiece(pos, white, "B") {
    // You can add additional initialization for the Bishop if needed
}

void Bishop::getAllMoves(ChessPiece* board[8][8]) {
    // Implement the Bishop's move logic here
    possibleMoves.clear();

    // Bishop moves diagonally
    // Adding all possible diagonal moves for the Bishop

    const int row = location.getRow();
    const int col = location.getCol();

    // Possible diagonal moves relative to the current position
    vector<pair<int, int>> bishopMoves = {
        {-1, -1}, {-1, 1},
        {1, -1}, {1, 1}
    };

    for (const auto &move : bishopMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            // Check if the destination is empty or contains an opponent's piece
            if (board[newRow][newCol] == nullptr) {
                possibleMoves.push_back(Coordinate(newRow, newCol));
            } else if (board[newRow][newCol]->getColour() != getColour()) {
                possibleMoves.push_back(Coordinate(newRow, newCol));
                break;  // Stop if an opponent's piece is encountered
            } else {
                break;  // Stop if own piece is encountered
            }

            newRow += move.first;
            newCol += move.second;
        }
    }

}

vector<Coordinate> Bishop::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Bishop's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}
