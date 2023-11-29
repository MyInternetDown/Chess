#ifndef __Knight__
#define __Knight__
#include "chesspiece.h"
#include <string>

class Knight : public ChessPiece {
public:
    Knight(vector<int> pos, bool Black);
    ~Knight();
};

#endif