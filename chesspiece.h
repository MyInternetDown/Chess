#ifndef ___ChessPiece___
#define ___ChessPiece___
#include <string>
#include <iostream>
#include <vector>
#include "enum.h"

using namespace std;

class Board;


class ChessPiece {
	vector<int> pos;
	bool Black;
public:
	ChessPiece(int pos, bool black);
	virtual Colour getColour();

	virtual ~ChessPiece()=0;
	virtual bool canMove(const std::string &start, const std::string &end, ChessPiece ** b) const=0;  
	bool isWhite() const;
	virtual bool isEmpty() const=0;
	int posn() const;
	void changePos(int posn);
	bool onRightEdge() const;
	bool onLeftEdge() const;
	bool onTopEdge() const;
	bool onBottomEdge() const;
	virtual void moved();
	virtual bool first() const;
	virtual char Type() const=0;

};

int getPos(const std::string &cmd); // converts a coordinate in the form of letter-number
// into the corresponding index in Board

std::string getCor(int index); // converts an index from Board into the 
// corresponding coordinate in the form letter-number

#endif 
