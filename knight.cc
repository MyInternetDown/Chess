// knight.cc

#include "knight.h"
#include <iostream>  // Include necessary headers for Coordinate class

Knight::Knight(string pos, string white)
    : ChessPiece(pos, white, "N") {
    // You can add additional initialization for the Knight if needed
}

vector<Coordinate> Knight::getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const {
    // Implement the Knight's move logic here
    vector<Coordinate> moves;

    // Knight moves in an L-shaped pattern
    // Adding all possible L-shaped moves for the Knight

    const int row = position.getRow();
    const int col = position.getCol();

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
            if (board[newRow][newCol].isEmpty() || board[newRow][newCol].getColour() != getColour()) {
                moves.push_back(Coordinate(newRow, newCol));
            }
        }
    }

    return moves;
}

vector<Coordinate> Knight::getAllAttackMoves(const vector<Coordinate> moves, const vector<vector<ChessPiece>> &board) const {
    // Implement the Knight's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : moves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()].getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}
