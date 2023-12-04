#ifndef KING_H
#define KING_H
#include <string>
#include "chesspiece.h"

class King : public ChessPiece {

public:
    bool checked;
    // Constructor
    King(Coordinate pos, string white);

    // Override the getAllMoves function for the King
    void getAllMoves(ChessPiece* board[8][8]) override;
    bool isChecked(ChessPiece* board[8][8]) override;
    // Get whether the king has moved
    void getAllCheckMoves(ChessPiece* board[8][8]) override;
    void getBlockPlaces(Coordinate attacker, ChessPiece* board[8][8]);
};

#endif
