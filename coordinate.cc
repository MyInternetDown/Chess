#include "coordinate.h"

using namespace std;

Coordinate::Coordinate(int row, int col): row{row}, col{col} {}

int Coordinate::getRow(void) const {
    return row;
}
int Coordinate::getCol(void) const {
    return col;
}
Coordinate::~Coordinate() {
    
}

string Coordinate::getStr() {
    std::ostringstream oss;
    oss << idxToCol.at(col) << row + 1;
    return oss.str();
}


ostream &operator<<(ostream &out, const Coordinate &c) {
    out << c.idxToCol.at(c.getCol()) << c.getRow() + 1;
    return out;
}

std::istream &operator>>(std::istream &in, Coordinate &c) {
    std::string input;
    in >> input;

    if (input.length() != 2) {
        throw std::invalid_argument("Invalid coordinate format");
    }

    c.col = c.colToIdx[input[0]];
    c.row = input[1] - '1';

    if (c.col < 0 || c.col >= 8 || c.row < 0 || c.row >= 8) {
        throw std::out_of_range("Coordinate out of bounds");
    }

    return in;
}


bool operator==(const Coordinate &left, const Coordinate &right) {
    return (left.getCol() == right.getCol() &&
           left.getRow() == right.getRow());
}

bool operator!=(const Coordinate &left, const Coordinate &right) {
    return !(left == right);
}
