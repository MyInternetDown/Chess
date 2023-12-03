#ifndef BISHOP_H
#define BISHOP_H
#include <string>
#include "chesspiece.h"

class Bishop : public ChessPiece {
public:
    // Constructor
    Bishop(Coordinate pos, string white);

    // Override the getAllMoves function for the Bishop
    void getAllMoves(ChessPiece* board[8][8]) override;

    // Override the getAllAttackMoves function for the Bishop
    vector<Coordinate> getAllAttackMoves(ChessPiece* board[8][8]) const override;
};
 


#endif
