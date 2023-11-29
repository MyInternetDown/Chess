#ifndef __BISHOP__
#define __BISHOP__
#include "chesspiece.h"
#include <string>

class Bishop : public ChessPiece {
public:
    Bishop(vector<int> pos, bool Black);
    ~Bishop();
    bool canMove(const vector<int> position, const vector<int> destination, const vector<vector<ChessPiece>>) const override;
    char Type() const override;
};

#endif
