#ifndef __KNIGHT__
#define __KNIGHT__
#include "chesspiece.h"
#include <string>

class Knight : public ChessPiece {
public:
    Knight(vector<int> pos, bool Black);
    ~Knight();
    bool canMove(const vector<int> position, const vector<int> destination, const vector<vector<ChessPiece>> board) const override;
    char Type() const override;
};

#endif
