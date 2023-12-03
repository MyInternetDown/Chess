#ifndef ___ChessPiece___
#define ___ChessPiece___
#include <string>
#include <iostream>
#include <vector>
#include "enum.h"
#include "coordinate.h"
#include <algorithm>
#include "observer.h"

using namespace std;

class Board;

class ChessPiece : public Observer{
	Coordinate location;
	PieceType piecetype;
	Colour colour;
	string pos;
	

public:
	vector<Coordinate> possibleMoves;
	bool hasMoved;
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

	
	// Destructor
	~ChessPiece();

	// Gets all possible moves on where this chesspiece and move to given a vector board of the locations of all the other pieces.
	virtual vector<Coordinate> getAllMoves(const Coordinate position, ChessPiece* board[8][8]) = 0;

	// Gets all possible locations where this piece would be under attack given its current position
	virtual vector<Coordinate> getAllDangerPositions(const Coordinate position, ChessPiece* board[8][8]) const;

	// Gets all possible locations where this piece can eat another piece
	virtual vector<Coordinate> getAllAttackMoves(const vector<Coordinate> moves, ChessPiece* board[8][8]) const =0;

	// Checks if the current piece can move to the current position noted down
	// to do
	//virtual bool canMove(const Coordinate position, const string destination, ChessPiece* board[8][8]) const;  

	Coordinate parseCoordinate(const std::string pos);

	// Get the Colour of the Piece
	virtual Colour getColour() const;
	// Get the position
	virtual Coordinate getPos() const;

	virtual PieceType getPiece() const;
	// Get the vecotrs of the possible moves
	//virtual vector<vector<int>> getPossibleMoves();
	// Gets the type of Piece
	string getStrType() const;
	// Gets the value of if the piece has moved
	virtual bool moved() const;
	// Check is Empty
	virtual bool isEmpty() const;

	void setEmpty();

	//void notify(Board &cb) override;
	
  	//SubscriptionType subType() override;

	virtual bool isChecked(ChessPiece* board[8][8]) const;

	// Move Piece
	void move(Coordinate moveHere) {
		//to do
	}
};

static vector<int> getPos(const std::string &cmd); // converts a coordinate in the form of letter-number
// into the corresponding index in Board

static std::string getCor(int index);

#endif 
