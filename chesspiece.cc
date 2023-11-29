#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>

using namespace std;

ChessPiece::ChessPiece(int pos, bool black) : pos{pos}, black{black} {}




virtual Colour getColour();

virtual vector<int> getPos();

virtual vector<vector<int>> getPossibleMoves();

virtual char Type() const = 0;

virtual void moved();


virtual ~ChessPiece() = 0;

void move(vector<int> moveHere);

vector<int> getPos(const std::string &cmd)
{

	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	vector<int> position = {row, col};
	return position;
}
