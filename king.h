#ifndef __King__
#define __King__
#include "chesspiece.h"
#include <string>

class King : public ChessPiece {
    bool hasMoved;
public:
    King(vector<int> pos, bool Black);
    ~King();
    bool canMove(const string &start, const string &end, ChessPiece **b) const override;
    bool isEmpty() const override;
    bool first() const override;
    char Type() const override;
    void moved () override;
};

#endif
