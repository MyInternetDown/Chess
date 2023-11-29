#ifndef __Rook__
#define __Rook__
#include "chesspiece.h"
#include <string>

class Rook : public ChessPiece {
public:
    Rook(vector<int> pos, bool Black);
    ~Rook();
    string getName();
    bool canMove(const vector<int> position, const vector<int> destination, const vector<vector<ChessPiece>>) const override;
    char Type() const override;
    void moved () override;
};

#endif