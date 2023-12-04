// knight.h

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece {
public:
    // Constructor
    Knight(Coordinate pos, string white);

    // Override the getAllMoves function for the Knight
    void getAllMoves(ChessPiece* board[8][8])  override;

    // Override the getAllAttackMoves function for the Knight
    vector<Coordinate> getAllAttackMoves(ChessPiece* board[8][8]) const override;
    vector<Coordinate> getAllCheckMoves(ChessPiece* board[8][8]) override;
};

#endif
