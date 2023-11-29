#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>

using namespace std;

ChessPiece::ChessPiece(int pos, bool black) : black{black} {}




Colour getColour();

vector<int> getPos();

vector<vector<int>> getPossibleMoves();

char Type() const = 0;

void moved();


~ChessPiece() = 0;

void move(vector<int> moveHere);

vector<int> getPos(const std::string &cmd)
{

	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	vector<int> position = {row, col};
	return position;
}
