#ifndef __KNIGHT__
#define __KNIGHT__
#include "chesspiece.h"
#include <string>

class Knight : public ChessPiece {
public:
    Knight(vector<int> pos, bool Black);
    ~Knight();
};

#endif
