#include "board.h"

// Constructor
Board::Board() : 
    turn{true}, 
    player1(H),   
    player1Pieces(),
    player2(H),
    player2Pieces(),
    isWon(false),
    td{nullptr}, 
    gd{nullptr}, 
    windowX{new Xwindow()} 
    {
    // Populate the board with ChessPiece objects at their respective positions
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // create an empty pointer to that place
            chessBoard[row][col] = nullptr;
        }
    }
}

bool Board::isValidSetup()  {
    // Check if there is exactly one white king and one black king
    int whiteKingCount = 0;
    int blackKingCount = 0;

    // Check if no pawns are on the first or last row
    for (int col = 0; col < 8; ++col) {
        if (chessBoard[0][col]->getStrType() == "P" || chessBoard[7][col]->getStrType() == "P") {
            return false;  // Pawn found on the first or last row
        }
    }

    // Check neither king is in check (you need to implement this logic in ChessPiece)
    // Assume there's a function isValidMove in ChessPiece that checks if a move is valid
    // and a function isChecked in ChessPiece that checks if a king is in check
    for (int row = 0; row < 8; ++row) {
        Coordinate temp = (1, 0);
        for (int col = 0; col < 8; ++col) {
            if (chessBoard[row][col]->getStrType() == "K") {
                if (chessBoard[row][col]->getColour() == Colour::White) {
                    ++whiteKingCount;
                    if (chessBoard[row][col]->isChecked(chessBoard)) {
                        return false;  // White king is in check
                    }
                } else {
                    ++blackKingCount;
                    if (chessBoard[row][col]->isChecked(chessBoard)) {
                        return false;  // Black king is in check
                    }
                }
            }
        }
    }
    if (whiteKingCount == 1 && blackKingCount == 1) {
        return true;
    }
    return false;
}


void Board::create(const string playerA, const string playerB){
    int n = 0;
    //td = new TextDisplay(n);
    //gd = new GraphicsDisplay(windowX ,n);
    player1 = convertStringToMoveType(playerA);
    player2 = convertStringToMoveType(playerB);
}

bool Board::getTurn(){
    return turn;
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


void Board::removePiece(const string position){
    Coordinate coord = parseCoordinate(position);
    int row = coord.getRow();
    int col = coord.getCol();
    delete chessBoard[row][col];
    chessBoard[row][col] = nullptr;
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