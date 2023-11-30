// bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece {
public:
    // Constructor
    Bishop(string pos, string white);

    // Override the getAllMoves function for the Bishop
    vector<Coordinate> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const override;
};

#endif
