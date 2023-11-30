// knight.h

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece {
public:
    // Constructor
    Knight(string pos, string white);

    // Override the getAllMoves function for the Knight
    vector<Coordinate> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const override;

    // Override the getAllAttackMoves function for the Bishop
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, const vector<vector<ChessPiece>> &board) const override;
};

#endif
