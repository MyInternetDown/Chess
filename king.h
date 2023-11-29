#ifndef __KING__
#define __KING__
#include "chesspiece.h"
#include <string>

class King : public ChessPiece {
    bool hasMoved;
public:
    King(vector<int> pos, bool Black);
    ~King();
    bool canMove(const vector<int> position, const vector<int> destination, const vector<vector<ChessPiece>>) const override;
    char Type() const override;
    void moved () override;
};

#endif
