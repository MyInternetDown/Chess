#ifndef __KING__
#define __KING__
#include "chesspiece.h"
#include <string>

class King : public ChessPiece {
    bool hasMoved;
public:
    King(vector<int> pos, bool Black);
    ~King();
    bool canMove(const Coordinate position, const Coordinate destination, const vector<vector<ChessPiece>> board) const override;
    bool isChecked(const vector<int> position, const vector<vector<ChessPiece>> board);
    char Type() const override;
    bool moved() override;
};

#endif
