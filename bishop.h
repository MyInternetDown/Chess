// bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece {
public:
    // Constructor
    Bishop(string pos, string white);

    // Override the getAllMoves function for the Bishop
    vector<Coordinate> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) override;
>>>>>>> 570d2e62dd90c96c09fc771e17a668d45387d77e
};
 
#endif
