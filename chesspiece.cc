#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>


// Constructor
ChessPiece::ChessPiece(Coordinate pos, string white, string type)
    : location(pos),
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
    possibleMoves.clear();
}

Colour ChessPiece::getColour() const{
    return colour;
}
	// Get the position
Coordinate ChessPiece::getPos() const{
    return location;
}

PieceType ChessPiece::getPiece() const{
    return piecetype;
}

std::vector<Coordinate> ChessPiece::getAllDangerPositions(ChessPiece* board[8][8]) const {
    std::vector<Coordinate> dangerSquares;

    // Iterate through the entire board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const ChessPiece *currentPiece = board[i][j];

            // Check if the current piece is of the opposing color and not an empty square
            if (!currentPiece->isEmpty() && currentPiece->getColour() != getColour()) {
                // Get all possible moves for the current piece and add them to dangerSquares
                std::vector<Coordinate> enemyMoves = this->possibleMoves;
                dangerSquares.insert(dangerSquares.end(), enemyMoves.begin(), enemyMoves.end());
            }
        }
    }

    // Sort and remove duplicates
    // to do
    //std::sort(dangerSquares.begin(), dangerSquares.end());
    dangerSquares.erase(std::unique(dangerSquares.begin(), dangerSquares.end()), dangerSquares.end());

    return dangerSquares;
}

ChessPiece::~ChessPiece() {
    // to do
}

string ChessPiece::getStrType() const {
}

char ChessPiece::getCharType() const {
    if (colour == White) {
        return getCharFromPieceType(piecetype);
    } else if (colour == Black) {
        return getCharFromPieceType(piecetype) + 32;
    }
}

bool ChessPiece::moved() const{
    return hasMoved;
}

bool ChessPiece::isChecked(ChessPiece* board[8][8]) const {
    return false;
    // to do
}
bool ChessPiece::isEmpty() const {
    return false;
    // to do
}




//void move(vector<int> moveHere);

vector<int> getPos(const std::string &cmd)
{
	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	vector<int> position = {row, col};
	return position;
}


std::string getCor(int index) {
    // Convert an index to a coordinate string, e.g., 0 -> "a1", 1 -> "b1", etc.
    int row = index / 8;
    int col = index % 8;
    char colChar = 'a' + col;
    return std::string(1, colChar) + std::to_string(row + 1);
}

