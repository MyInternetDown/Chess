#ifndef __Pawn__
#define __Pawn__
#include "chesspiece.h"
#include <string>

class Pawn : public ChessPiece {
public:
    Pawn(vector<int> pos, bool Black);
    string getName();
    bool isBlocked(vector<int> pos);
    bool promote(vector<int> pos);
    bool enPassant(vector<int>pos, vector<vector<int>>prevMove);
};

#endif