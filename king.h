#ifndef KING_H
#define KING_H
#include "chesspiece.h"
#include <string>

// king.h


class King : public ChessPiece {

public:
    // Constructor
    King(string pos, string white);

    // Override the getAllMoves function for the King
    vector<Coordinate> getAllMoves(const Coordinate position, const ChessPiece ***board) override;
    bool isChecked(ChessPiece ***board) override;
    // Get whether the king has moved
};

#endif
