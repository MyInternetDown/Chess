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
    void getAllBlockKing(vector<Coordinate> protectPos) override;
    void adjustPossibleMoves(ChessPiece* board[8][8]) override;
    void getAllLevel4Moves(ChessPiece* board[8][8]) override;
    void getAllPotentialMoves(ChessPiece* board[8][8]) override;
};
void printVector(const std::vector<Coordinate>& vec);

#endif
