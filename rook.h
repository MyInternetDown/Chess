// rook.h

#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece {
    bool hasMoved;  // New variable to track whether the rook has moved

public:
    // Constructor
    Rook(string pos, string white);

    // Override the getAllMoves function for the Rook
    vector<Coordinate> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const override;

    // Override the getAllAttackMoves function for the Rook
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, const vector<vector<ChessPiece>> &board) const override;

    // Get whether the rook has moved
    bool moved() override;
};

#endif
