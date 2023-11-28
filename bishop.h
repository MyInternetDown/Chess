#ifndef __Bishop__
#define __Bishop__
#include "chesspiece.h"
#include <string>

class Bishop : public ChessPiece {
public:
    Bishop(vector<int> pos, bool Black);
    string getName();
    bool isValidMove(vector<int> pos);
    bool isBlocked(vector<int> pos);
    bool move (vector<int> pos);
};

#endif
