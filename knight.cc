// knight.cc

#include "knight.h"
#include <iostream>  // Include necessary headers for Coordinate class

Knight::Knight(Coordinate pos, string white)
    : ChessPiece(pos, white, "N") {
    // You can add additional initialization for the Knight if needed
}

void Knight::getAllMoves(ChessPiece* board[8][8]) {
    // Implement the Knight's move logic here
    possibleMoves.clear();

    // Knight moves in an L-shaped pattern
    // Adding all possible L-shaped moves for the Knight

    const int row = location.getRow();
    const int col = location.getCol();

    // Possible moves relative to the current position
    vector<pair<int, int>> knightMoves = {
        {-2, -1}, {-2, 1},
        {-1, -2}, {-1, 2},
        {1, -2}, {1, 2},
        {2, -1}, {2, 1}
    };

    for (const auto &move : knightMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            // Check if the destination is empty or contains an opponent's piece
            if (board[newRow][newCol] == nullptr || board[newRow][newCol]->getColour() != getColour()) {
                possibleMoves.push_back(Coordinate(newRow, newCol));
            }
        }
    }

}

vector<Coordinate> Knight::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Knight's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

vector<Coordinate> Knight::getAllCheckMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> checkMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getPiece() == K) {
            checkMoves.push_back(move);
        }
    }

    return checkMoves;
}
