// bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece {
public:
    // Constructor
    Bishop(string pos, string white);

    // Override the getAllMoves function for the Bishop
    vector<Coordinate> getAllMoves(const Coordinate position, const ChessPiece ***board) override;

    // Override the getAllAttackMoves function for the Bishop
    vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, const ChessPiece ***board) const override;
};
 

Coordinate parseCoordinate(const std::string pos);

#endif
