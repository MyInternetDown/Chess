#ifndef ___ChessPiece___
#define ___ChessPiece___
#include <string>
#include <iostream>
#include <vector>
#include "enum.h"
#include "coordinate.h"

using namespace std;


class ChessPiece {
	Coordinate location;
	PieceType piecetype;
	Colour colour;
	string pos;
	string white;
	string type;
	vector<Coordinate> possibleMoves;

public:
	// Constructor of the Chesspiece
	ChessPiece(string pos, string white, string type);

    // Copy constructor
    ChessPiece(const ChessPiece &other);
    // Move constructor
    ChessPiece(ChessPiece &&other);
    // Copy assignment operator
    ChessPiece &operator=(const ChessPiece &other);
    // Move assignment operator
    ChessPiece &operator=(ChessPiece &&other);

	// Gets all possible moves on where this chesspiece and move to given a vector board of the locations of all the other pieces.
	virtual vector<vector<int>> getAllMoves(const Coordinate position, const vector<vector<ChessPiece>>board);

	// Gets all possible locations where this piece would be under attack given its current position
	virtual vector<vector<int>> getAllDangerMoves(const Coordinate position, const vector<vector<ChessPiece>>board);

	// Gets all possible locations where this piece can eat another piece
	virtual vector<vector<int>> getAllAttackMoves(const Coordinate position, const vector<vector<ChessPiece>>board);

	// Checks if the current piece can move to the current position noted down
	virtual bool canMove(const Coordinate position, const string destination, const vector<vector<ChessPiece>>board);  

	Coordinate parseCoordinate(const std::string &pos);

	

	// Get the Colour of the Piece
	virtual Colour getColour();
	// Get the position
	virtual vector<int> getPos();
	// Get the vecotrs of the possible moves
	virtual vector<vector<int>> getPossibleMoves();
	// Gets the type of Piece
	char getType() const;
	// Gets the value of if the piece has moved
	virtual bool moved();
	// Check is Empty
	virtual bool isEmpty();

	void setEmpty();


	// Destructor
	~ChessPiece();

	// Move Piece
	void move(vector<int> moveHere);
};

vector<int> getPos(const std::string &cmd); // converts a coordinate in the form of letter-number
// into the corresponding index in Board

std::string getCor(int index); // converts an index from Board into the 
// corresponding coordinate in the form letter-number

#endif 
