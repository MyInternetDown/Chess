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
    void getAllCheckMoves(ChessPiece* board[8][8]) override;
    void adjustPossibleMoves(ChessPiece* board[8][8]) override;
    void getAllLevel4Moves(ChessPiece* board[8][8]) override;
};

#endif
