// rook.h

#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece {
public:
    // Constructor
    Rook(string pos, string white);

    // Override the getAllMoves function for the Rook
    vector<Coordinate> getAllMoves(const Coordinate position, ChessPiece* board[8][8])  override;

    // Override the getAllAttackMoves function for the Rook
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, ChessPiece* board[8][8]) const override;

};

#endif
