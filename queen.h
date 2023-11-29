#ifndef __QUEEN__
#define __QUEEN__
#include "chesspiece.h"
#include <string>

class Queen : public ChessPiece {
public:
    Queen(vector<int> pos, bool Black);
    ~Queen();
    bool canMove(const vector<int> position, const vector<int> destination, const vector<vector<ChessPiece>>) const override;
    char Type() const override;
};

#endif
