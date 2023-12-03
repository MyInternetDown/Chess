// queen.h

#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece {
public:
    // Constructor
    Queen(string pos, string white);

    // Override the getAllMoves function for the Queen
    vector<Coordinate> getAllMoves(const Coordinate position, ChessPiece* board[8][8]) override;

    // Override the getAllAttackMoves function for the Queen
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, ChessPiece* board[8][8]) const override;
};

#endif
