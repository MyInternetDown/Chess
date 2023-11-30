#include <string>
#include "chesspiece.h"
#include <sstream>
#include <vector>

using namespace std;

// Constructor
ChessPiece::ChessPiece(string pos, string white, string type)
    : location(parseCoordinate(pos)),
      piecetype(parsePieceType(type)),
      colour(parseColour(white)),
      pos(pos),
      white(white),
      type(type),
      hasMoved(false){
    // Initialize other members if needed
}

// Copy constructor
ChessPiece::ChessPiece(const ChessPiece &other)
    : location(other.location),
      piecetype(other.piecetype),
      colour(other.colour),
      pos(other.pos),
      white(other.white),
      type(other.type)
         {
    // Copy other members if needed
}

// Move constructor
ChessPiece::ChessPiece(ChessPiece &&other)
    : location(std::move(other.location)),
      piecetype(std::move(other.piecetype)),
      colour(std::move(other.colour)),
      pos(std::move(other.pos)),
      white(std::move(other.white)),
      type(std::move(other.type)) {
    // Move other members if needed
}

// Copy assignment operator
ChessPiece &ChessPiece::operator=(const ChessPiece &other) {
    if (this != &other) {
        location = other.location;
        piecetype = other.piecetype;
        colour = other.colour;
        pos = other.pos;
        white = other.white;
        type = other.type;
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
        pos = std::move(other.pos);
        white = std::move(other.white);
        type = std::move(other.type);
        // Move other members if needed
    }
    return *this;
}

// Set all values to default or no-values
void ChessPiece::setEmpty() {
    colour = Colour::Void;
    piecetype = PieceType::V;
    // Set type and white based on the default values in the maps
    type = strToPiece.at("V");
    white = strToColour.at("NoColour");
    // You might want to reset other members to their default values
    // or update them according to your specific requirements
    possibleMoves.clear();
}



Coordinate parseCoordinate(const std::string &pos) {
    Coordinate c;
    istringstream iss(pos);
    iss >> c;
    return c;
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

std::vector<Coordinate> ChessPiece::getAllDangerPositions(const Coordinate position, const std::vector<std::vector<ChessPiece>> &board) const {
    std::vector<Coordinate> dangerSquares;

    // Iterate through the entire board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const ChessPiece &currentPiece = board[i][j];

            // Check if the current piece is of the opposing color and not an empty square
            if (!currentPiece.isEmpty() && currentPiece.getColour() != getColour()) {
                // Get all possible moves for the current piece and add them to dangerSquares
                std::vector<Coordinate> enemyMoves = currentPiece.getAllMoves(Coordinate(i, j), board);
                dangerSquares.insert(dangerSquares.end(), enemyMoves.begin(), enemyMoves.end());
            }
        }
    }

    // Sort and remove duplicates
    std::sort(dangerSquares.begin(), dangerSquares.end());
    dangerSquares.erase(std::unique(dangerSquares.begin(), dangerSquares.end()), dangerSquares.end());

    return dangerSquares;
}

string ChessPiece::getStrType() const {
    return type;
}

bool ChessPiece::moved() const{
    return hasMoved;
}

void move(vector<int> moveHere);

vector<int> getPos(const std::string &cmd)
{

	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	vector<int> position = {row, col};
	return position;
}
