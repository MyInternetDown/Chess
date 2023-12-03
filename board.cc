#include "board.h"

// Constructor
Board::Board() {
    // Populate the board with ChessPiece objects at their respective positions
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // create an empty pointer to that place
            chessBoard[row][col] = nullptr;
        }
    }
}

void Board::init(const std::string position, const std::string type, const std::string color) {
    // Find the row and column indices based on the location string
    Coordinate coord = parseCoordinate(position);
    int row = coord.getRow();
    int col = coord.getCol();

    // Create the appropriate ChessPiece based on the type
    if (type == "K") {
        chessBoard[row][col] = new King(position, color);
    } else if (type == "Q") {
        chessBoard[row][col] =  new Queen(position, color);
    } else if (type == "B") {
        chessBoard[row][col] = new Bishop(position, color);
    } else if (type == "N") {
        chessBoard[row][col] = new Knight(position, color);
    } else if (type == "R") {
        chessBoard[row][col] = new Rook(position, color);
    } else if (type == "P") {
        chessBoard[row][col] = new Pawn(position, color);
    }
    // Handle other piece types as needed
}


// Function to get a reference to the chess piece at a specific position
ChessPiece &Board::at(const Coordinate &pos) {
    // Add boundary checking if needed
    return *chessBoard[pos.getRow()][pos.getCol()];
}

// Function to get a const reference to the chess piece at a specific position
const ChessPiece &Board::at(const Coordinate &pos) const {
    // Add boundary checking if needed
    return *chessBoard[pos.getRow()][pos.getCol()];
}

// Function to check if a position is within the bounds of the board
bool Board::isValidPosition(const Coordinate &pos) const {
    return pos.getRow() >= 0 && pos.getRow() < 8 &&
           pos.getCol() >= 0 && pos.getCol() < 8;
}

// Destructor
Board::~Board() {}


Coordinate parseCoordinate(const std::string pos) {
    Coordinate c;
    istringstream iss(pos);
    iss >> c;
    return c;
}