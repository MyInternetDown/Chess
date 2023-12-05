#ifndef ___ChessPiece___
#define ___ChessPiece___

#include <iostream>
#include <vector>
#include "enum.h"
#include "coordinate.h"
#include <algorithm>
#include "observer.h"
#include <cstdlib>

class Board;

class ChessPiece {
	PieceType piecetype;
	
	string pos;
	

public:
	Colour colour;
	Coordinate previousLoc;
	Coordinate location;
	vector<Coordinate> blockKing;
	vector<Coordinate> evadeMoves;
	vector<Coordinate> attackMoves;
	vector<Coordinate> dangerSquares;
	vector<Coordinate> checkMoves;
	vector<Coordinate> protectKing;

	vector<Coordinate> possibleMoves;
	bool hasMoved;
	// Constructor of the Chesspiece
	ChessPiece(Coordinate pos, string white, string type);


    // Copy constructor
    ChessPiece(const ChessPiece &other);
    // Move constructor
    ChessPiece(ChessPiece &&other);
    // Copy assignment operator
    ChessPiece &operator=(const ChessPiece &other);
    // Move assignment operator
    ChessPiece &operator=(ChessPiece &&other);

	
	// Destructor
	virtual ~ChessPiece();

	// Gets all possible moves on where this chesspiece and move to given a vector board of the locations of all the other pieces.
	virtual void getAllMoves(ChessPiece* board[8][8]) = 0;

	// Gets all possible locations where this piece would be under attack given its current position
	virtual void getAllDangerPositions(ChessPiece* board[8][8]);

	// Gets all possible locations where this piece can eat another piece
	virtual void getAllAttackMoves(ChessPiece* board[8][8]);
	virtual void getAllEvadeMoves(ChessPiece* board[8][8]);
	virtual void getAllBlockKing(vector<Coordinate> protectPos);

	virtual void getAllCheckMoves(ChessPiece* board[8][8]) = 0;
	virtual void updateFirst(ChessPiece* board[8][8]);
	virtual void update(ChessPiece* board[8][8]);

	// Checks if the current piece can move to the current position noted down
	// to do
	//virtual bool canMove(const Coordinate position, const string destination, ChessPiece* board[8][8]) const;  

	Coordinate parseCoordinate(const std::string pos);

	// Get the Colour of the Piece
	virtual Colour getColour() const;
	// Get the position
	virtual Coordinate getPos() const;

	int getPieceRow() const;
	int getPieceCol() const;
	Coordinate getRandMove() const;

	virtual PieceType getPiece() const;
	// Get the vecotrs of the possible moves
	//virtual vector<vector<int>> getPossibleMoves();
	// Gets the type of Piece
	// Gets the value of if the piece has moved
	virtual bool moved() const;
	// Check is Empty
	virtual bool isEmpty() const;

	char getCharType() const;

	void setEmpty();

	virtual bool isChecked(ChessPiece* board[8][8]);

	// Move Piece
	void move(Coordinate moveHere);
};

#endif 
