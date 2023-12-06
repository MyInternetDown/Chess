// pawn.cc

#include "pawn.h"

Pawn::Pawn(Coordinate pos, string white)
    : ChessPiece(pos, white, "P") {  // Initialize hasMoved to false
    // You can add additional initialization for the Pawn if needed
}

// Get all possible moves for the Pawn
void Pawn::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    int forwardDirection = (getColour() == Colour::White) ? 1 : -1;

    // Pawn moves forward
    int newRow = row + forwardDirection;
    if (newRow >= 0 && newRow < 8 && board[newRow][col] == nullptr) {
        possibleMoves.push_back(Coordinate(newRow, col));

        // Pawn's double move from starting position
        if (!hasMoved) {
            newRow += forwardDirection;
            if (newRow >= 0 && newRow < 8 && board[newRow][col]==nullptr) {
                possibleMoves.push_back(Coordinate(newRow, col));
            }
        }
    }

    // Pawn attacks diagonally
    for (int colOffset : {-1, 1}) {
        int newCol = col + colOffset;
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            !(board[newRow][newCol] == nullptr) && board[newRow][newCol]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(newRow, newCol));
        }
    }
}

/*
vector<Coordinate> Pawn::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Queen's attack moves logic here
    vector<Coordinate> attackMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

*/

// Get all moves that put the opponent's king in check
void Pawn::getAllCheckMoves(ChessPiece* board[8][8]) {

    checkMoves.clear();
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Pawn temp(move, tempCol);
        board[location.getRow()][location.getCol()] = nullptr;
        temp.getAllMoves(board);
        for (auto &fMove : temp.possibleMoves) {
            if ((board[fMove.getRow()][fMove.getCol()] != nullptr) &&
                (board[fMove.getRow()][fMove.getCol()]->getPiece() == K) ){
                checkMoves.push_back(move);
            }
        }
        board[location.getRow()][location.getCol()] = this;
    }
}

// Adjust possible moves considering opponent's moves
void Pawn::adjustPossibleMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> tempMoves;
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Pawn temp(move, tempCol);
        board[location.getRow()][location.getCol()] = nullptr;
        ChessPiece *tempPiece = board[move.getRow()][move.getCol()];
        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = &temp;

        // Update possible moves for all pieces on the board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }

        // Check if the opponent's king is not in a checked state after the move
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && board[i][j]->getPiece() == K && temp.getColour() == board[i][j]->getColour()) {
                    if (!board[i][j]->isChecked(board)) {
                        tempMoves.push_back(move);
                    }
                }
            }
        }

        // Restore the original state of the board
        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = tempPiece;
        board[location.getRow()][location.getCol()] = this;

        // Update possible moves for all pieces on the board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }
    }
    possibleMoves = tempMoves;
}

void Pawn::getAllLevel4Moves(ChessPiece* board[8][8]) {
    level4Moves.clear();
    for (const auto &move : attackMoves) {
        string tempCol = colourToStr.find(colour)->second;
        Pawn temp(move, tempCol);
        board[location.getRow()][location.getCol()] = nullptr;
        ChessPiece *tempPiece = board[move.getRow()][move.getCol()];
        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = &temp;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }
        getAllDangerPositions(board);
        for (const auto& coord : attackMoves) {
            if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
                level4Moves.push_back(coord);
            }
        
        }

        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = tempPiece;
        board[location.getRow()][location.getCol()] = this;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }
    }
    //printVector1(level4Moves);

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Pawn temp(move, tempCol);
        board[location.getRow()][location.getCol()] = nullptr;
        temp.getAllMoves(board);
        for (auto &fMove : temp.possibleMoves) {
            if ((board[fMove.getRow()][fMove.getCol()] != nullptr) &&
                (board[fMove.getRow()][fMove.getCol()]->getPiece() == K) ){
                level4Moves.push_back(move);
            }
        }
        board[location.getRow()][location.getCol()] = this;
    }
    //printVector1(level4Moves);

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Pawn temp(move, tempCol);
        board[location.getRow()][location.getCol()] = nullptr;
        ChessPiece *tempPiece = board[move.getRow()][move.getCol()];
        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = &temp;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }
        getAllDangerPositions(board);
        for (const auto& coord : possibleMoves) {
            if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
                level4Moves.push_back(coord);
            }
        }
        //board[move.getRow()][move.getCol()] = nullptr;
        board[move.getRow()][move.getCol()] = tempPiece;
        board[location.getRow()][location.getCol()] = this;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && temp.getColour() != board[i][j]->getColour()) {
                    board[i][j]->getAllMoves(board);
                }
            }
        }
    }
    //printVector1(level4Moves);
}



// Function to print the contents of a vector of Coordinates
void printVector1(const std::vector<Coordinate>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

