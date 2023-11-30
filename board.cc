#include "board.h"

// Constructor
Board::Board() {
    board.resize(8, std::vector<ChessPiece>(8, ChessPiece("a1", "NoColour", "V")));  // Assuming "a1" is the starting position

    // Populate the board with ChessPiece objects at their respective positions
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Create a coordinate string for the current position
            std::string coordStr = getCor(row * 8 + col);

            // Create a ChessPiece with no color, void type, and the current coordinate
            board[row][col] = ChessPiece(coordStr, "NoColour", "V");
        }
    }
}

// Copy constructor
Board::Board(const Board &other) : board(other.board) {}

// Move constructor
Board::Board(Board &&other) noexcept : board(std::move(other.board)) {}

// Copy assignment operator
Board &Board::operator=(const Board &other) {
    if (this != &other) {
        board = other.board;
    }
    return *this;
}

// Move assignment operator
Board &Board::operator=(Board &&other) noexcept {
    if (this != &other) {
        board = std::move(other.board);
    }
    return *this;
}

// Function to get a reference to the chess piece at a specific position
ChessPiece &Board::at(const Coordinate &pos) {
    // Add boundary checking if needed
    return board[pos.getRow()][pos.getCol()];
}

// Function to get a const reference to the chess piece at a specific position
const ChessPiece &Board::at(const Coordinate &pos) const {
    // Add boundary checking if needed
    return board[pos.getRow()][pos.getCol()];
}

// Function to check if a position is within the bounds of the board
bool Board::isValidPosition(const Coordinate &pos) const {
    return pos.getRow() >= 0 && pos.getRow() < 8 &&
           pos.getCol() >= 0 && pos.getCol() < 8;
}

// Destructor
Board::~Board() {}
