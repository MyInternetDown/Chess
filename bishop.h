#ifndef __Bishop__
#define __Bishop__
#include "chesspiece.h"
#include <string>

class Bishop : public ChessPiece {
public:
    Bishop(vector<int> pos, bool Black);
    bool canMove(const string &start, const string &end, ChessPiece **b) const override;
    bool isEmpty() const override;
    char Type() const override;
};

#endif
