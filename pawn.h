// pawn.h

#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece {

public:
    // Constructor
    Pawn(string pos, string white);

    // Override the getAllMoves function for the Pawn
    vector<Coordinate> getAllMoves(const Coordinate position, ChessPiece* board[8][8]) override;
    bool promote(vector<int> pos);
    bool enPassant(vector<int>pos, vector<vector<int>>prevMove);

    // Get whether the pawn has moved
};

#endif
