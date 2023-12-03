// knight.h

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece {
public:
    // Constructor
    Knight(string pos, string white);

    // Override the getAllMoves function for the Knight
    vector<Coordinate> getAllMoves(const Coordinate position,ChessPiece* board[8][8])  override;

    // Override the getAllAttackMoves function for the Knight
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, ChessPiece* board[8][8]) const override;
};

#endif
