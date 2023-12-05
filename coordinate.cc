#include "coordinate.h"

using namespace std;

// ctor: initializes a Coordinate with given row and column values.
Coordinate::Coordinate(int row, int col): row{row}, col{col} {}

// getter function: returns the row value of a Coordinate.
int Coordinate::getRow(void) const {
    return row;
}

// getter function: returns the column value of a Coordinate.
int Coordinate::getCol(void) const {
    return col;
}

// dtor
Coordinate::~Coordinate() {
    
}

// getter function: returns a string representation of a Coordinate.
string Coordinate::getStr() {
    // Use stringstream to concatenate column and row into a string
    std::ostringstream oss;
    oss << idxToCol.at(col) << row + 1;
    return oss.str();
}

// outputs the Coordinate to the stream.
ostream &operator<<(ostream &out, const Coordinate &c) {
    // output the column character and row number 
    out << c.idxToCol.at(c.getCol()) << c.getRow() + 1;
    return out;
}

// reads a Coordinate from the stream
std::istream &operator>>(std::istream &in, Coordinate &c) {
    std::string input;
    in >> input;

    // ensure the input has exactly two characters
    if (input.length() != 2) {
        throw std::invalid_argument("Invalid coordinate format");
    }

    // convert the column character to index using the colToIdx map
    c.col = c.colToIdx[input[0]];
    // convert the row character to index
    c.row = input[1] - '1';

    // check if the resulting Coordinate is within the valid chessboard bounds
    if (c.col < 0 || c.col >= 8 || c.row < 0 || c.row >= 8) {
        throw std::out_of_range("Coordinate out of bounds");
    }

    return in;
}

// checks if two Coordinates are equal
bool operator==(const Coordinate &left, const Coordinate &right) {
    return (left.getCol() == right.getCol() &&
           left.getRow() == right.getRow());
}

// checks if two Coordinates are not equal
bool operator!=(const Coordinate &left, const Coordinate &right) {
    return !(left == right);
}
