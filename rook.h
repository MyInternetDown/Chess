// rook.h

#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece {
public:
    // Constructor
    Rook(Coordinate pos, string white);

    // Override the getAllMoves function for the Rook
    void getAllMoves(ChessPiece* board[8][8])  override;

    // Override the getAllAttackMoves function for the Rook
    vector<Coordinate> getAllAttackMoves(ChessPiece* board[8][8]) const override;
    vector<Coordinate> getAllCheckMoves(ChessPiece* board[8][8]) override;
};

#endif
