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

using namespace std;




class Board {



private:

	bool turn;
	MoveType player1;
	vector<ChessPiece*> player1Pieces;
	MoveType player2;
	vector<ChessPiece*> player2Pieces;
	bool isWon;
	TextDisplay *td; // The text display.
  	GraphicsDisplay *gd; // graphics display
  	Xwindow *windowX;
	std::vector<Observer*> observers;


	

public:

	ChessPiece *chessBoard[8][8];
	char chessDisplay[8][8];
    // Constructor
    Board();

    // Copy constructor
    Board(const Board &other);

    // Move constructor
    Board(Board &&other);

	void init(const std::string position, const std::string type, const std::string color);

	void create(const string playerA, const string playerB);

	void removePiece(Coordinate pos, bool needNotify = false);

	void reset();

	bool getTurn();
    // Copy assignment operator
    Board &operator=(const Board &other);

    // Move assignment operator
    Board &operator=(Board &&other);

	bool isValidSetup();

    // Function to get a reference to the chess piece at a specific position
    ChessPiece &at(const Coordinate &pos);

    // Function to get a const reference to the chess piece at a specific position
    const ChessPiece &at(const Coordinate &pos) const;

    // Function to check if a position is within the bounds of the board
    bool isValidPosition(const Coordinate &pos) const;

    // Destructor

	void move();

    ~Board();

	void notify(Board *cb);

	SubscriptionType subType();

	void notifyAllObservers();

	void attach(Observer *o);

	void detach(Observer *o);

};

#endif



/*
// Board objects 
class Board {
	Piece **board; // an array of 64 Piece pointers
	bool isTurnWhite;
	bool inCheck;
	bool gameOver;
	Scoreboard *s;
	GraphicsDisplay *gd = nullptr;
	Player *p1;
	Player *p2;

public:
	Board(int p1, int p2);
	~Board();

	// setup methods
	void endGame(std::string cmd); // cmd is "black", "white", "white resigns",
	// "black resigns" or "draw";
	void clearBoard(); // clears all the current pieces from the board 
	void normalSetup(); // default configuration for a game
	void place(char piece, const std::string &cmd); // only used during setup mode 
	bool validBoard(); // only used during setup mode, checks if board is in a valid setup
	void newPlayers(int player1, int player2); // generate two new players
	void setTurn(std::string colour); //sets turn to colour

	// game logic methods 
	void move(const std::string &start, const std::string &end);
	bool isCheck(bool isWhite); //
	bool isCheckmate(); 
	bool isStalemate();
	bool canPawnPromote();
	bool testMove(const std::string &start, const std::string &end);


	

	//  
	Piece *getPiece(const std::string &cmd); // returns a pointer to the piece stored at
	// cmd
	Piece ** getBoard(); // provides a copy of the board
	// for other classes to reference

	//
	bool getTurnStatus() const;
	void printScore() const;
	bool isGameOver(); 
	void gameOn(); // sets gameOver flag to false
	void setgd(GraphicsDisplay *g);
	std::string sendToDisplay() const;

	// 
	bool isP1computer(); // checks if P1 is a computer
	bool isP2computer(); // checks if P2 is a computer
	void makeCompMove();

	std::string findKing(bool isWhite) const;
};
*/


