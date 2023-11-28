#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>

using namespace std;

vector<int> getPos(const std::string &cmd) {

	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
    vector<int> position = {row, col};
	return position;
}


