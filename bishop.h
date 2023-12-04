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
    void getAllCheckMoves(ChessPiece* board[8][8]) override;

};
 


#endif
