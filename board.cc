#include "board.h"
// Constructor
 
const char WHITE = ' ';
const char BLACK = '_';

Board::Board() : 
    turn{true}, 
    player1{H},   
    player1Pieces{},
    player2{H},
    player2Pieces{},
    isWon{false},
    td{nullptr}
    //gd{nullptr}, 
    //windowX{new Xwindow()} 
    {
    // Populate the board with ChessPiece objects at their respective positions
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // create an empty pointer to that place
            chessBoard[row][col] = nullptr;
            if ((row + col) % 2 == 0) {
                chessDisplay[row][col] = BLACK;
            } else {
                chessDisplay[row][col] = WHITE;
            }
        }
    }
}

bool Board::isValidSetup()  {
    //cerr << "enter valid" << endl;
    gameStart = false;
    // Check if there is exactly one white king and one black king
    int whiteKingCount = 0;
    int blackKingCount = 0;

    // Check if no pawns are on the first or last row
    for (int col = 0; col < 8; ++col) {
        if (chessBoard[0][col] != nullptr && chessBoard[7][col] != nullptr){
            //cerr << col << "checking......" << endl;
            if (chessBoard[0][col]->getCharType() == 'p' || chessBoard[7][col]->getCharType() == 'P') {
                return false;  // Pawn found on the first or last row
            }
        }
    }
    //cerr << "pawn ok" << endl;

    // Check neither king is in check (you need to implement this logic in ChessPiece)
    // Assume there's a function isValidMove in ChessPiece that checks if a move is valid
    // and a function isChecked in ChessPiece that checks if a king is in check
    for (int row = 0; row < 8; ++row) {
        Coordinate temp = (1, 0);
        for (int col = 0; col < 8; ++col) {
            if (chessBoard[row][col] != nullptr){
                if (chessBoard[row][col]->getCharType() == 'K' || 
                    chessBoard[row][col]->getCharType() == 'k') {
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
    }
    if (whiteKingCount == 1 && blackKingCount == 1) {
        gameStart = true;
        cerr << "found true valid " << endl;
        return true;
    }
    cerr << "found false valid " << endl;
    return false;
}


void Board::create(const string playerA, const string playerB){
    //cerr << "increate" << endl;
    td = new TextDisplay();
    //cerr << "1" << endl;
    //gd = new GraphicsDisplay(windowX ,n);
    attach(td);
    //cerr << "2" << endl;
    // to do make attach
    player1 = convertStringToMoveType(playerA);
    //cerr << "3" << endl;
    player2 = convertStringToMoveType(playerB);
    //cerr << "4" << endl;

}

bool Board::getTurn(){
    return turn;
}

void Board::reset(){
    for (ChessPiece* piece : player1Pieces) {
        delete piece;
    }
    for (ChessPiece* piece : player2Pieces) {
        delete piece;
    }
    player1Pieces.clear();
    player2Pieces.clear();

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            chessBoard[row][col] = nullptr;
            if ((row * 8 + col) % 2 == 0) {
                chessDisplay[row][col] = WHITE;
            } else {
                chessDisplay[row][col] = BLACK;
            }
        }
    }
    player1 = H;
    player2 = H;
    isWon = false;
    turn = false;
}

// Setup Piece
void Board::init(const std::string position, const std::string type, const std::string color) {
    // Find the row and column indices based on the location string
    Coordinate coord;
    istringstream pos(position);
    pos >> coord;
    int row = coord.getRow();
    int col = coord.getCol();

    //cerr << row << " " << col << endl;



    removePiece(coord);

    // Create the appropriate ChessPiece based on the type
    if (type == "K" || type == "k") {
        chessBoard[row][col] = new King(coord, color);
    } else if (type == "Q" || type == "q") {
        chessBoard[row][col] =  new Queen(coord, color);
    } else if (type == "B" || type == "b") {
        chessBoard[row][col] = new Bishop(coord, color);
    } else if (type == "N" || type == "n") {
        chessBoard[row][col] = new Knight(coord, color);
    } else if (type == "R" || type == "r") {
        chessBoard[row][col] = new Rook(coord, color);
    } else if (type == "P" || type == "p") {
        chessBoard[row][col] = new Pawn(coord, color);
    }

    chessDisplay[row][col] = chessBoard[row][col]->getCharType();
    //cerr << chessBoard[row][col]->getCharType() << "chekingsadklfas;jfkasl;fdjal;dfj;" << endl;

    if (color == "White") {
        player1Pieces.push_back(chessBoard[row][col]);
    } else if (color == "Black") {
        player2Pieces.push_back(chessBoard[row][col]);
    }

    chessDisplay[row][col] = chessBoard[row][col]->getCharType();

    //notifyAllObservers();
    // Handle other piece types as needed
    
}

void Board::defaultSetup(){
    cerr << "enter default " << endl;

    init("a2", "P", "White");
    init("b2", "P", "White");
    init("c2", "P", "White");
    init("d2", "P", "White");
    init("e2", "P", "White");
    init("f2", "P", "White");
    init("g2", "P", "White");
    init("h2", "P", "White");
    init("a1", "R", "White");
    init("b1", "N", "White");
    init("c1", "B", "White");
    init("d1", "Q", "White");
    init("e1", "K", "White");
    init("f1", "B", "White");
    init("g1", "N", "White");
    init("h1", "R", "White");

    // Black pieces
    init("a7", "P", "Black");
    init("b7", "P", "Black");
    init("c7", "P", "Black");
    init("d7", "P", "Black");
    init("e7", "P", "Black");
    init("f7", "P", "Black");
    init("g7", "P", "Black");
    init("h7", "P", "Black");
    init("a8", "r", "Black");
    init("b8", "n", "Black");
    init("c8", "b", "Black");
    init("d8", "q", "Black");
    init("e8", "k", "Black");
    init("f8", "b", "Black");
    init("g8", "n", "Black");
    init("h8", "r", "Black");
}

// Remove
void Board::removePiece(Coordinate coord, bool needNotify){
    int row = coord.getRow();
    int col = coord.getCol();
    //cerr << "remove" << endl;
    if (chessBoard[row][col] != nullptr) {
        cerr << "in remove not null" << endl;
        if (chessBoard[row][col]->getColour() == White) {
            for(int i = 0; i < player1Pieces.size(); i++) {
                if (player1Pieces[i] == chessBoard[row][col]) {
                    player1Pieces.erase(player1Pieces.begin()+i);
                    break;
                }
            }
        } else {
            for(int i = 0; i < player2Pieces.size(); i++) {
                if (player1Pieces[i] == chessBoard[row][col]) {
                    player2Pieces.erase(player2Pieces.begin()+i);
                    break;
                }
            }
        }
        delete chessBoard[row][col];
        chessBoard[row][col] = nullptr;
        if (row * 8 + col % 2 == 0) {
            chessDisplay[row][col] == WHITE;
        }
        else {
            chessDisplay[row][col] == BLACK;
        }
    }

    //cerr << "out" << endl;
    if (needNotify) {
        notifyAllObservers();
    }
}

void Board::updatePieces() {
    cerr << "update piece" << endl;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // create an empty pointer to that place
            if (chessBoard[row][col] != nullptr) {
                cerr << "updatein  " << row << " " << col << endl;
                chessBoard[row][col]->getAllMoves(chessBoard);
            }
        }
    }
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

void Board::changeTurn(string color) {
    if (parseColour(color) == White) {
        turn = true;
    } else {
        turn = false;
    }
}


void Board::move() {
    // check error handling if ther are no more pieces to move to do
    
    bool found = false;
    if (turn && player1 != H) {
        cerr << " computer 1 " << endl;
        if (player1 == L1) {
            while (!found) {
                int randomIndex = rand() % player1Pieces.size();
                ChessPiece* piece = player1Pieces[randomIndex];
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    return;
                }
            }
        }
    }

    if (!turn && player2 != H) {
        cerr << " computer 2" << endl;
        //cerr << "computer turn" << endl;
        if (player2 == L1) {
            //cerr << " level robot" <<endl;
            while (!found) {
                //cerr << "stop" << player2Pieces.size() << endl;
                int randomIndex = rand() % player2Pieces.size();
                //cerr << "random " << randomIndex << endl;
                ChessPiece* piece = player2Pieces[randomIndex];
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                }
            }
        }
    }

}


// Destructor
Board::~Board() {
    reset();
    delete td;
    //delete gd;
    observers.clear();
}


void Board::notifyAllObservers() {
  for (auto &observer : observers) {
        if (observer->subType() == SubscriptionType::All) {
            observer->notify(chessDisplay);
        }
    }
}

void Board::attach(Observer *o) { 
  observers.emplace_back(o);
}

void Board::detach(Observer *o){
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}


void Board::humanMove(string startPos, string endPos, char promote) {
    cerr << "humanMove" << endl;
    Coordinate coordStart;
    Coordinate coordEnd;
    istringstream pos1(startPos);
    istringstream pos2(endPos);
    pos1 >> coordStart;
    pos2 >> coordEnd;
    if (canMove(coordStart, coordEnd)) {
        absMove(coordStart, coordEnd);
    }
}

bool Board::canMove(Coordinate startPos, Coordinate endPos) {
    //cerr << "canMove" << endl;
    ChessPiece* piece = chessBoard[startPos.getRow()][startPos.getCol()];

    if (piece != nullptr) {
        //cerr << "found a piece at pos" << endl;
        if ((getTurn() && piece->getColour() == White) || 
            (!getTurn() && piece->getColour() == Black)) {
            auto it = find(piece->possibleMoves.begin(), 
            piece->possibleMoves.end(), endPos);

            if (it != piece->possibleMoves.end()) {
                return true;
            }
        }
    }
    return false;
}


void Board::absMove(Coordinate startPos, Coordinate endPos){
   
    // make for displayer to do
    if (chessBoard[endPos.getRow()][endPos.getCol()] != nullptr) {
        removePiece(endPos);
    }
    ChessPiece* pieceToMove = chessBoard[startPos.getRow()][startPos.getCol()];
    cerr << "absMove" << startPos << " " << endPos <<  " " << pieceToMove->getCharType() << endl;

    // Check if there is a piece at the source location
    assert(pieceToMove != nullptr);

    chessBoard[startPos.getRow()][startPos.getCol()] = nullptr;

    // Move the piece to the destination location
    chessBoard[endPos.getRow()][endPos.getCol()] = pieceToMove;

    // Update the piece's location (if needed)
    pieceToMove->move(endPos);

    chessDisplay[endPos.getRow()][endPos.getCol()] = pieceToMove->getCharType();
    chessDisplay[startPos.getRow()][startPos.getCol()] = 
    (startPos.getRow() + endPos.getCol() & 2 == 0) ? BLACK : WHITE;


    updatePieces();
    turn = !turn;
    notifyAllObservers();
}


Coordinate parseCoordinate(const std::string pos) {
    Coordinate c;
    istringstream iss(pos);
    iss >> c;
    return c;
}