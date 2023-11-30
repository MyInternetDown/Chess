#ifndef __BISHOP__
#define __BISHOP__
#include "chesspiece.h"
#include <string>

class Bishop : public ChessPiece {
public:
    Bishop(string white, string type, string pos);
    bool canMove(
        const Coordinate position, const string destination, 
        const vector<vector<ChessPiece>>board
    ) const override;
    char Type() const override;
};
 
#endif
