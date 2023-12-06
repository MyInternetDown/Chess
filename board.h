#ifndef ___BOARD___
#define ___BOARD___

#include <string>
#include "player.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "coordinate.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "enum.h"
#include "window.h"
#include <vector>
#include "observer.h"
#include <cassert>  


using namespace std;




class Board {



private:
	// Private data members
	bool turn;
	bool initialized;
	bool isWon;
	TextDisplay *td; // The text display.
  	GraphicsDisplay *gd; // graphics display
  	Xwindow *windowX;
	std::vector<Observer*> observers;
	vector<ChessPiece*> player2Pieces;
	vector<ChessPiece*> player1Pieces;
	
public:
	// Public data members
	MoveType player1;
	MoveType player2;
	int player1Score;
	int player2Score;
	ChessPiece *chessBoard[8][8];
	char chessDisplay[8][8];
    // Constructor
    Board();

    // Copy constructor
    Board(const Board &other);

    // Move constructor
    Board(Board &&other);

	 // Member functions for board setup and initialization
	void init(const std::string position, const std::string type, const std::string color);
	void create(const string playerA, const string playerB);
	void defaultSetup();
	void reset();

	// Member functions for managing pieces on the board
	void removePiece(Coordinate pos, bool needNotify = false);
	void updatePieces();
	void updateCheck(ChessPiece* king, bool check = false);
	bool checkPromote();
	void promote(string type);
    
	// Member functions for game state and player actions
	bool getTurn();
    // Copy assignment operator
    Board &operator=(const Board &other);

    // Move assignment operator
    Board &operator=(Board &&other);

	bool checkCastle();
	void castle();
	void checkComputerCastle();

	void resign();

	bool isValidSetup();

    // Function to get a reference to the chess piece at a specific position
    ChessPiece &at(const Coordinate &pos);

    // Function to get a const reference to the chess piece at a specific position
    const ChessPiece &at(const Coordinate &pos) const;

    // Function to check if a position is within the bounds of the board
    bool isValidPosition(const Coordinate &pos) const;

	void checkWin(Colour player);
	
	bool checkStale(Colour player);

    // Destructor

	void changeTurn(string color);

	bool moveL1(Colour player);
	bool moveL2(Colour player);
	bool moveL3(Colour player);
	bool moveL4(Colour player);
	void move();

	void checkComputerPromote();

	void humanMove(string startPos, string endPos, char promote = ' ');

	bool canMove(Coordinate startPos, Coordinate endPos);

	void absMove(Coordinate startPos, Coordinate endPos);

    ~Board();

	// Observer pattern related functions
	SubscriptionType subType();
	void notifyAllObservers();
	void attach(Observer *o);
	void detach(Observer *o);
};

int getDifference(Coordinate from, Coordinate curr, bool horizontal = true);

#endif


