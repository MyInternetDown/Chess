#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>

using namespace std;

ChessPiece::ChessPiece(string pos, string white, string type)
    : 	location{parseCoordinate(pos)},
		piecetype{parsePieceType(type)},
        colour{parseColour(white)} {
	
}


Coordinate parseCoordinate(const std::string &pos) {
    Coordinate c;
    istringstream iss(pos);
    iss >> c;
    return c;
}

Colour getColour();

vector<int> getPos();

vector<vector<int>> getPossibleMoves();

char getType();

void moved();

void move(vector<int> moveHere);

vector<int> getPos(const std::string &cmd)
{

	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	vector<int> position = {row, col};
	return position;
}
