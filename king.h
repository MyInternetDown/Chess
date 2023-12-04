#ifndef KING_H
#define KING_H
#include <string>
#include "chesspiece.h"

class King : public ChessPiece {

public:
    // Constructor
    King(Coordinate pos, string white);

    // Override the getAllMoves function for the King
    void getAllMoves(ChessPiece* board[8][8]) override;
    vector<Coordinate> getAllAttackMoves(ChessPiece* board[8][8]) const override;
    bool isChecked(ChessPiece* board[8][8]) const override;
    // Get whether the king has moved
    vector<Coordinate> getAllCheckMoves(ChessPiece* board[8][8]) override;
};

#endif
