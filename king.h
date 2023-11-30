#ifndef KING_H
#define KING_H
#include "chesspiece.h"
#include <string>

// king.h


class King : public ChessPiece {
    bool hasMoved;  // New variable to track whether the king has moved

public:
    // Constructor
    King(string pos, string white);

    // Override the getAllMoves function for the King
    vector<Coordinate> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const override;
    bool isChecked(const Coordinate position, const vector<vector<ChessPiece>> board);
    // Get whether the king has moved
    bool moved() override;
};

#endif
