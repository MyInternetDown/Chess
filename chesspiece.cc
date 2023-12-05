#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;



// Constructor
ChessPiece::ChessPiece(Coordinate pos, string white, string type)
    : location(pos),
      previousLoc(pos),
      piecetype(parsePieceType(type)),
      colour(parseColour(white)),
      hasMoved(false){
    // Initialize other members if needed
}

// Copy constructor
ChessPiece::ChessPiece(const ChessPiece &other)
    : location(other.location),
      piecetype(other.piecetype),
      colour(other.colour),
      hasMoved(other.hasMoved)
    {
    // Copy other members if needed
}

// Move constructor
ChessPiece::ChessPiece(ChessPiece &&other)
    : location(std::move(other.location)),
      piecetype(std::move(other.piecetype)),
      colour(std::move(other.colour)),
      hasMoved(std::move(other.hasMoved)) {
    // Move other members if needed
}

// Copy assignment operator
ChessPiece &ChessPiece::operator=(const ChessPiece &other) {
    if (this != &other) {
        location = other.location;
        piecetype = other.piecetype;
        colour = other.colour;
        hasMoved = other.hasMoved;
        // Copy other members if needed
    }
    return *this;
}

// Move assignment operator
ChessPiece &ChessPiece::operator=(ChessPiece &&other) {
    if (this != &other) {
        location = std::move(other.location);
        piecetype = std::move(other.piecetype);
        colour = std::move(other.colour);
        hasMoved = std:: move(other.hasMoved);
        // Move other members if needed
    }
    return *this;
}

// Set all values to default or no-values
void ChessPiece::setEmpty() {
    colour = Colour::Void;
    piecetype = PieceType::V;
    // Set type and white based on the default values in the maps
    // You might want to reset other members to their default values
    // or update them according to your specific requirements
   // possibleMoves.clear();
}

// Get the color of the chess piece
Colour ChessPiece::getColour() const{
    return colour;
}

// Get the position of the chess piece
Coordinate ChessPiece::getPos() const{
    return location;
}

// Get the type of the chess piece
PieceType ChessPiece::getPiece() const{
    return piecetype;
}

// Update the attack moves of the chess piece based on the current board state
void ChessPiece::getAllAttackMoves(ChessPiece* board[8][8]){

    attackMoves.clear();

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if ((board[move.getRow()][move.getCol()] != nullptr) &&
            board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

}

// Update the possible moves and adjust them based on specific piece rules
void ChessPiece::updateFirst(ChessPiece* board[8][8]) {
    getAllMoves(board);
    adjustPossibleMoves(board);
}

// Update the chess piece's information, 
void ChessPiece::update(ChessPiece* board[8][8]) {
    blockKing.clear();
    getAllDangerPositions(board);
    //cerr << "update 1" << endl;
    //cerr << "update 2" << endl;
    getAllEvadeMoves(board);
    getAllAttackMoves(board);
    //cerr << "update 3" << endl;
    getAllCheckMoves(board);
    //cerr << "update 4" << endl;
}

// Get all positions on the board that are considered dangerous for the piece
void ChessPiece::getAllDangerPositions(ChessPiece* board[8][8]) {
    dangerSquares.clear();

    // Iterate through the entire board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const ChessPiece* currentPiece = board[i][j];

            // Check if the current piece is of the opposing color and not an empty square
            if (currentPiece != nullptr && currentPiece->getColour() != getColour()) {
                // Get all possible moves for the current piece and add them to dangerSquares
                dangerSquares.insert(dangerSquares.end(), currentPiece->possibleMoves.begin(), currentPiece->possibleMoves.end());
            }
        }
    }

    // Sort and remove duplicates
    // to do
    //std::sort(dangerSquares.begin(), dangerSquares.end());
    dangerSquares.erase(std::unique(dangerSquares.begin(), dangerSquares.end()), dangerSquares.end());
}

// Get all possible moves that allow the piece to escape danger
void ChessPiece::getAllEvadeMoves(ChessPiece* board[8][8]) {
    evadeMoves.clear(); 
    if (std::find(dangerSquares.begin(), dangerSquares.end(), location) != dangerSquares.end()) {
        for (const auto& coord : possibleMoves) {
            if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
                evadeMoves.push_back(coord);
            }
        }
    }
}

// Get all possible moves that allow the piece to block the opponent's king
void ChessPiece::getAllBlockKing(vector<Coordinate> protectPos){
    blockKing.clear();
    for (const auto& coord : possibleMoves) {
        if (std::find(protectPos.begin(), protectPos.end(), coord) != protectPos.end()) {
            if (coord != location) {
                blockKing.push_back(coord);
            }
        }
    }
}

//void getAllBlockKing(ChessPiece* board[8][8]) {

// dtor
ChessPiece::~ChessPiece() {
    possibleMoves.clear();
    dangerSquares.clear();
    attackMoves.clear();
    checkMoves.clear();
    evadeMoves.clear();
}

// Get a random move from the possible moves of the chess piece
Coordinate ChessPiece::getRandMove() const {
    int randomIndex = rand() % possibleMoves.size();
    return possibleMoves[randomIndex];
}

// Get the character representation of the chess piece based on its color
char ChessPiece::getCharType() const {
    if (colour == White) {
        return getCharFromPieceType(piecetype);
    } else if (colour == Black) {
        return getCharFromPieceType(piecetype) + 32;
    }
}

// Check if the chess piece has moved
bool ChessPiece::moved() const{
    return hasMoved;
}

bool ChessPiece::isChecked(ChessPiece* board[8][8]) {
    return false;
    // to do
}

bool ChessPiece::isEmpty() const {
    return false;
    // to do
}

// Move the chess piece to a new location
void ChessPiece::move(Coordinate moveHere) {
    location = moveHere;
}




//void move(vector<int> moveHere);
