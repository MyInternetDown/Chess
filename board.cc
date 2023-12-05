#include "board.h"
// Constructor
 
const char WHITE = ' ';
const char BLACK = '_';

Board::Board() : 
    turn{true}, 
    player1Score{0},
    player1{H},   
    player1Pieces{},
    player2Score{0},
    player2{H},
    player2Pieces{},
    isWon{false},
    initialized{false},
    //gd{nullptr}, 
    // windowX{new Xwindow()} 
    td{nullptr}
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
    cerr << "enter valid" << endl;
    initialized = false;
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
    cerr << "pawn ok" << endl;

    // Check neither king is in check (you need to implement this logic in ChessPiece)
    // Assume there's a function isValidMove in ChessPiece that checks if a move is valid
    // and a function isChecked in ChessPiece that checks if a king is in check
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (chessBoard[row][col] != nullptr){
                //cerr << " found a piece" << endl;
                if (chessBoard[row][col]->getPiece() == K) {
                    //cerr << "found a king" << endl;
                    if (chessBoard[row][col]->getColour() == White) {
                        ++whiteKingCount;
                        if (chessBoard[row][col]->isChecked(chessBoard)) {
                            //cerr << "white king not good" << endl;
                            return false;  // White king is in check
                        }
                    } else {
                        ++blackKingCount;
                        if (chessBoard[row][col]->isChecked(chessBoard)) {
                            //cerr << "balck king not good" << endl;
                            return false;  // Black king is in check
                        }
                    }
                }
            }
        }
    }
    cerr << whiteKingCount << " " << blackKingCount << " count" << endl;

    // check if there is exactly one white king and one black king
    if (whiteKingCount == 1 && blackKingCount == 1 ) {
        cerr << "found true valid " << endl;
        initialized = true;
        return true;
    }
    cerr << "found false valid " << endl;
    return false;
}

// function to create the chessboard and set up the game
void Board::create(const string playerA, const string playerB){
    //cerr << "increate" << endl;
    td = new TextDisplay();
    //cerr << "1" << endl;
    //gd = new GraphicsDisplay(windowX);
    attach(td);
    //attach(gd);
    //cerr << "2" << endl;
    // to do make attach
    player1 = convertStringToMoveType(playerA);
    //cerr << "3" << endl;
    player2 = convertStringToMoveType(playerB);
    //cerr << "4" << endl;
}

// get the current turn
bool Board::getTurn(){
    return turn;
}

// reset the game state
void Board::reset(){
    // clear the chessboard
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            chessBoard[row][col] = nullptr;
            // set the display color for each square
            if ((row + col) % 2 == 0) {
                chessDisplay[row][col] = BLACK;
            } else {
                chessDisplay[row][col] = WHITE;
            }
        }
        notifyAllObservers();
    }
    // delete and clear player pieces
    for (ChessPiece* piece : player1Pieces) {
        delete piece;
    }
    for (ChessPiece* piece : player2Pieces) {
        delete piece;
    }
    player1Pieces.clear();
    player2Pieces.clear();
    initialized = false;
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

    //chessDisplay[row][col] = chessBoard[row][col]->getCharType();
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

// set up the default chessboard
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

void Board::resign() {
    if (turn) {
        player2Score++;
    } else {
        player1Score++;
    }
    reset();
}

// Remove
void Board::removePiece(Coordinate coord, bool needNotify){
    int row = coord.getRow();
    int col = coord.getCol();
    //cerr << "remove" << endl;
    if (chessBoard[row][col] != nullptr) {
        //cerr << "in remove not null" << endl;
        if (chessBoard[row][col]->getColour() == White) {
            for(int i = 0; i < player1Pieces.size(); i++) {
                if (player1Pieces[i] == chessBoard[row][col]) {
                    player1Pieces.erase(player1Pieces.begin()+i);
                    break;
                }
            }
        } else {
            for(int i = 0; i < player2Pieces.size(); i++) {
                if (player2Pieces[i] == chessBoard[row][col]) {
                    player2Pieces.erase(player2Pieces.begin()+i);
                    break;
                }
            }
        }
        delete chessBoard[row][col];
        chessBoard[row][col] = nullptr;
        if ((row + col) % 2 == 0) {
            chessDisplay[row][col] == BLACK;
        }
        else {
            chessDisplay[row][col] == WHITE;
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

                //cerr << "updatein  " << row << " " << col << " " << chessBoard[row][col]->getCharType() <<endl;
                chessBoard[row][col]->updateFirst(chessBoard);
            }
        }
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // create an empty pointer to that place
            if (chessBoard[row][col] != nullptr) {

                //cerr << "updatein  " << row << " " << col << " " << chessBoard[row][col]->getCharType() <<endl;
                chessBoard[row][col]->update(chessBoard);
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

// to move a piece on the board
void Board::move() {
    // check if the game is initialized
    if (!initialized){
        cerr << "not init game" << endl;
        return;
    }
    // check error handling if there are no more pieces to move to do
    bool found = false;
    // check if it's the turn of player 1 (White) and the player is not human
    if (turn && player1 != H) {
        cerr << " computer 1 " << endl;
        if (player1 == L1) {
            // level 1: move to block the opponent's king
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            while (!found) {
                int randomIndex = rand() % player1Pieces.size();
                ChessPiece* piece = player1Pieces[randomIndex];
                //cerr << " checkpoint" << randomIndex << endl;
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        } else if (player1 == L2) {
            // level 2: move to block, check, or attack the opponent
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->checkMoves.empty()) {
                    cerr << "checking" << endl;
                    absMove(piece->location, piece->checkMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->attackMoves.empty()) {
                    cerr << "attacking ___________________" << endl;
                    absMove(piece->location, piece->attackMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            while (!found) {
                int randomIndex = rand() % player1Pieces.size();
                ChessPiece* piece = player1Pieces[randomIndex];
                //cerr << " checkpoint" << randomIndex << endl;
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        } else if (player1 == L3) {
            // level 3: move to block, evade, check, or attack the opponent
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->evadeMoves.empty()) {
                    cerr << "evading" << endl;
                    absMove(piece->location, piece->evadeMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->checkMoves.empty()) {
                    cerr << "checking" << endl;
                    absMove(piece->location, piece->checkMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player1Pieces) {
                if (!piece->attackMoves.empty()) {
                    cerr << "attacking ___________________" << endl;
                    absMove(piece->location, piece->attackMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            while (!found) {
                int randomIndex = rand() % player1Pieces.size();
                ChessPiece* piece = player1Pieces[randomIndex];
                //cerr << " checkpoint" << randomIndex << endl;
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        }

    }
    // check if it's the turn of player 2 (Black) and the player is not human
    if (!turn && player2 != H) {
        cerr << " computer 2" << endl;
        //cerr << "computer turn" << endl;
        if (player2 == L1) {
            // level 1: move to block the opponent's king
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            //cerr << " level robot" <<endl;
            while (!found) {
                //cerr << "stop" << player2Pieces.size() << endl;
                int randomIndex = rand() % player2Pieces.size();
                //cerr << "random " << randomIndex << endl;
                ChessPiece* piece = player2Pieces[randomIndex];
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        }else if (player2 == L2) {
            // level 2: move to block, check, or attack the opponent
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->checkMoves.empty()) {
                    cerr << "checking" << endl;
                    absMove(piece->location, piece->checkMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->attackMoves.empty()) {
                    cerr << "attacking ___________________" << endl;
                    absMove(piece->location, piece->attackMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            while (!found) {
                int randomIndex = rand() % player2Pieces.size();
                ChessPiece* piece = player2Pieces[randomIndex];
                //cerr << " checkpoint" << randomIndex << endl;
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        } else if (player2 == L3) {
            // level 3: move to block, evade, check, or attack the opponent
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->blockKing.empty()) {
                    cerr << " bloooooooooooooock +++++++++++" << endl;
                    absMove(piece->location, piece->blockKing[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->evadeMoves.empty()) {
                    cerr << "evading" << endl;
                    absMove(piece->location, piece->evadeMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->checkMoves.empty()) {
                    cerr << "checking" << endl;
                    absMove(piece->location, piece->checkMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            for (ChessPiece* piece : player2Pieces) {
                if (!piece->attackMoves.empty()) {
                    cerr << "attacking ___________________" << endl;
                    absMove(piece->location, piece->attackMoves[0]);
                    checkComputerPromote();
                    return;
                }
            }
            while (!found) {
                int randomIndex = rand() % player2Pieces.size();
                ChessPiece* piece = player2Pieces[randomIndex];
                //cerr << " checkpoint" << randomIndex << endl;
                if (!piece->possibleMoves.empty()) {
                    found = true;
                    absMove(piece->location, piece->getRandMove());
                    checkComputerPromote();
                    return;
                }
            }
        }
    }
}

// check if a computer move results in pawn promotion
void Board::checkComputerPromote() {
    if (checkPromote()) {
        std::vector<std::string> options = {"Q", "R", "B", "N"};
        int randomIndex = std::rand() % options.size();
        cerr << "promote to " << options[randomIndex] << endl;
        promote(options[randomIndex]);
    }
}

// Destructor
Board::~Board() {
    //cerr << "delete board1" << endl;
    for (ChessPiece* piece : player1Pieces) {
        delete piece;
    }
    //cerr << "delete board1-----" << endl;
    for (ChessPiece* piece : player2Pieces) {
        delete piece;
    }
    player1Pieces.clear();
    player2Pieces.clear();
    //cerr << "delete board2" << endl;
    detach(td);
    //detach(gd); // dispaly
    //cerr << "delete board3" << endl;
    delete td;
    //delete gd;
}

// update the check status for a king and its pieces
void Board::updateCheck(ChessPiece* king, bool check) {
    for (int i =0; i < 8; ++ i ) {
        for (int j = 0; j < 8; ++j) {
            if(chessBoard[i][j] != nullptr && chessBoard[i][j]->getColour() == king->getColour() && check) {
                chessBoard[i][j]->getAllBlockKing(king->protectKing);
            }
        }
    }
}

// check for stalemate for a player
bool Board::checkStale(Colour player) {
   // return false;

    if (player == White) {
        // check for stalemate for white player
        for (const auto &chessPiece: player1Pieces) {
            if (chessPiece->possibleMoves.size() != 0) {
                return false;
            }
        }
        isWon = true;
        return true;

    
    } else {
        // check for stalemate for black player
        for (const auto &chessPiece: player2Pieces) {
            if (chessPiece->possibleMoves.size() != 0) {
                return false;
            }
        }
        isWon = true;
        return true;
    }
    return false;
}

// promote a pawn to a specified piece type
void Board::promote(string type) {
    cerr << "enter promotion" << endl;
    if (!turn) {
        // promote pawn on the 7th rank for white
        cerr << "1" << endl;
        for (const auto& piece : chessBoard[7]) {
            if (piece != nullptr && piece->getPiece() == P) {
                Coordinate temp(piece->location);
                removePiece(temp);
                init(temp.getStr(), type, "White");
                chessDisplay[temp.getRow()][temp.getCol()] =  chessBoard[temp.getRow()][temp.getCol()]->getCharType();
            }
        }
    } else {
        // promote pawn on the 8th rank for black
        cerr << "2" << endl;
        for (const auto& piece : chessBoard[0]) {
            if (piece != nullptr && piece->getPiece() == P) {
                Coordinate temp(piece->location);
                removePiece(temp);
                init(temp.getStr(), type, "Black");
                chessDisplay[temp.getRow()][temp.getCol()] =  chessBoard[temp.getRow()][temp.getCol()]->getCharType();
            }
        }
    } 

    notifyAllObservers();
}

// check if pawn promotion is possible
bool Board::checkPromote() {
    cerr << "check promote" << endl;
    // check if there is a pawn on the 1st or 8th rank
    for (const auto& piece : chessBoard[0]) {
        if (piece != nullptr && piece->getPiece() == P) {
            return true;
        }
    }

    // Check the 8th row
    for (const auto& piece : chessBoard[7]) {
        cerr << "pickels" << endl;
        if (piece != nullptr && piece->getPiece() == P) {
            return true;
        }
    }
    return false;
}

// check for checkmate and update the game state
void Board::checkWin(Colour player) {
   // return;
    cerr << "check for check mate" << endl;
    if (player == White) {
        // check for checkmate for white player
        cerr << "enter Check" << endl;
        for (ChessPiece* piece : player1Pieces) {
            if(piece->getPiece() == K) {
                //cerr << "found king    " << piece->isChecked(chessBoard) <<  endl;
                //cerr << "found king    " << piece->evadeMoves.size() <<  endl;
                if (piece->isChecked(chessBoard)) {
                    updateCheck(piece, true);
                    cerr << "is in check" << endl;
                    if (piece->evadeMoves.size() == 0) {
                        cerr << "check no blocks" << endl;
                        for (ChessPiece* pieceOther : player1Pieces) {
                            if(pieceOther->blockKing.size() != 0) {
                                return;
                            }
                        }
                        cerr << "Black WIN ===========================================" << endl;
                        isWon = true;
                        player2Score++;
                    }
                }
            }
        }
    } else {
        // check for checkmate for black player
        for (ChessPiece* piece : player2Pieces) {
            if(piece->getPiece() == K) {
                if (piece->isChecked(chessBoard)) {
                    updateCheck(piece, true);
                    if (piece->evadeMoves.size() == 0) {
                        for (ChessPiece* pieceOther : player2Pieces) {
                            if(pieceOther->blockKing.size() != 0) {
                                return;
                            }
                        }
                        cerr << "White WIN ===========================================" << endl;
                        isWon = true;
                        player1Score++;
                    }
                }
            }
        }
    }
}

// notify all observers (display) about changes in the game state
void Board::notifyAllObservers() {
  for (auto &observer : observers) {
        if (observer->subType() == SubscriptionType::All) {
            observer->notify(chessDisplay);
        }
    }
}

// attach an observer to the board
void Board::attach(Observer *o) { 
  observers.emplace_back(o);
}

// detach an observer from the board
void Board::detach(Observer *o){
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

// when a human player to make a move
void Board::humanMove(string startPos, string endPos, char promote) {
    if(!initialized) {
        cerr << "not init game" << endl;
    }
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

// check if a move from startPos to endPos is valid
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

// execute an absolute move on the chessboard
void Board::absMove(Coordinate startPos, Coordinate endPos){
    assert(startPos != endPos);
   
    // make for displayer to do
    if (chessBoard[endPos.getRow()][endPos.getCol()] != nullptr) {
        removePiece(endPos);
    }
    ChessPiece* pieceToMove = chessBoard[startPos.getRow()][startPos.getCol()];
    cerr << "absMove ----------------------------" << startPos << " " << endPos <<  " " << pieceToMove->getCharType() << endl;

    // Check if there is a piece at the source location
    assert(pieceToMove != nullptr);

    chessBoard[startPos.getRow()][startPos.getCol()] = nullptr;

    // Move the piece to the destination location
    chessBoard[endPos.getRow()][endPos.getCol()] = pieceToMove;

    // Update the piece's location (if needed)
    if (pieceToMove->getPiece() == P) {
        pieceToMove->previousLoc = startPos;
    }
    pieceToMove->move(endPos);

    // update the display with the moved piece
    chessDisplay[endPos.getRow()][endPos.getCol()] = pieceToMove->getCharType();
    chessDisplay[startPos.getRow()][startPos.getCol()] = 
    ((startPos.getRow() + startPos.getCol()) % 2 == 0) ? BLACK : WHITE;
    pieceToMove->hasMoved = true;

    // switch the turn to the other player
    turn = !turn;
    updatePieces();
    cerr << "move finished" << chessBoard[endPos.getRow()][endPos.getCol()]->getCharType() << endl;

    // notify all observers (display) about the changes
    notifyAllObservers();

    // check for stalemate and checkmate conditions, update scores, and reset the game if it's won
    if (chessBoard[endPos.getRow()][endPos.getCol()]->getColour() == White) {
        if(checkStale(Black)) {
            cerr << "Black STALE ===========================================" << endl;
            player1Score++;
            player2Score++;
            
        } else {
            checkWin(Black);
        }
    } else {
        cerr << "black" << endl;
        if(checkStale(White)) {
            cerr << "White STALE ===========================================" << endl;
            player1Score++;
            player2Score++;
            
        } else {
            checkWin(White);
        }
    }
    if (isWon) {
        cerr << "GAME OVER" << endl;
        reset();
    }
}

// parse a string representing a chess position into a Coordinate
Coordinate parseCoordinate(const std::string pos) {
    Coordinate c;
    istringstream iss(pos);
    iss >> c;
    return c;
}
