#include "coordinate.h"

using namespace std;

Coordinate::Coordinate(int row, int col): row{row}, col{col} {}

int Coordinate::getRow(void) const {
    return row;
}
int Coordinate::getCol(void) const {
    return col;
}
Coordinate::~Coordinate() {}

ostream &operator<<(ostream &out, const Coordinate &c) {
    out << c.idxToCol.at(c.getCol()) << c.getRow() + 1;
    return out;
}

istream &operator>>(istream &in, Coordinate &c) {
    char col;
    int row;
    in >> col;
    in >> row;

    c.row = row - 1;
    c.col = c.colToIdx.at(tolower(col));
    return in;
}

bool operator==(const Coordinate &left, const Coordinate &right) {
    return (left.getCol() == right.getCol() &&
           left.getRow() == right.getRow());
}

bool operator!=(const Coordinate &left, const Coordinate &right) {
    return !(left == right);
}
