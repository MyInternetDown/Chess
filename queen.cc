// queen.cc

#include "queen.h"
#include <iostream>

Queen::Queen(string pos, string white)
    : ChessPiece(pos, white, "Q") {
    // You can add additional initialization for the Queen if needed
}

vector<Coordinate> Queen::getAllMoves(const Coordinate position, const ChessPiece ***board) {
    // Implement the Queen's move logic here
    vector<Coordinate> moves;

    // Queen moves diagonally and linearly (horizontally and vertically)
    // Adding all possible moves for the Queen

    const int row = position.getRow();
    const int col = position.getCol();

    // Possible moves relative to the current position
    vector<pair<int, int>> queenMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : queenMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            // Check if the destination is empty or contains an opponent's piece
            if (board[newRow][newCol] == nullptr) {
                moves.push_back(Coordinate(newRow, newCol));
            } else if (board[newRow][newCol]->getColour() != getColour()) {
                moves.push_back(Coordinate(newRow, newCol));
                break;  // Stop if an opponent's piece is encountered
            } else {
                break;  // Stop if own piece is encountered
            }

            newRow += move.first;
            newCol += move.second;
        }
    }

    return moves;
}

vector<Coordinate> Queen::getAllAttackMoves(const vector<Coordinate> moves, const ChessPiece ***board) const {
    // Implement the Queen's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : moves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}
