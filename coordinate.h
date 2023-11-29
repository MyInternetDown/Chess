#ifndef COORD_H
#define COORD_H
#include <iostream>
#include <map>

using namespace std;

class Coordinate {
    protected:
        int row;
        int col;

    public:

        map<int, char> idxToCol = {
            {0, 'a'},
            {1, 'b'},
            {2, 'c'},
            {3, 'd'},
            {4, 'e'},
            {5, 'f'},
            {6, 'g'},
            {7, 'h'}
        };

        map<char, int> colToIdx = {
            {'a', 0},
            {'b', 1},
            {'c', 2},
            {'d', 3},
            {'e', 4},
            {'f', 5},
            {'g', 6},
            {'h', 7}
        };

        Coordinate(int row = 0, int col = 0);
        int getRow(void) const;
        int getCol(void) const;
        friend std::istream &operator>>(std::istream &in, Coordinate &c);
};

bool operator==(const Coordinate &left, const Coordinate &right);
bool operator!=(const Coordinate &left, const Coordinate &right);
std::ostream &operator<<(std::ostream &out, const Coordinate &c);

#endif