// rook.cc

#include "rook.h"

Rook::Rook(Coordinate pos, string white)
    : ChessPiece(pos, white, "R"){  // Initialize hasMoved to false
    // You can add additional initialization for the Rook if needed
}

// Get all possible moves for the Rook
void Rook::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    // Rook moves vertically
    for (int newRow = row + 1; newRow < 8; ++newRow) {
        if (board[newRow][col] == nullptr) {
            possibleMoves.push_back(Coordinate(newRow, col));
        } else if (board[newRow][col]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(newRow, col));
	        break;
        } else {
            break;
        }
    }
    for (int newRow = row - 1; newRow >= 0; --newRow) {
        if (board[newRow][col] == nullptr) {
            possibleMoves.push_back(Coordinate(newRow, col));
        } else if (board[newRow][col]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(newRow, col));
	        break;
        } else {
            break;
        }
    }


    // Rook moves horizontally
    for (int newCol = col + 1; newCol < 8; ++newCol) {
        if (board[row][newCol] == nullptr) {
            possibleMoves.push_back(Coordinate(row, newCol));
        } else if (board[row][newCol]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(row, newCol));
	        break;
        } else {
            break;
        }
    }

    for (int newCol = col - 1; newCol >= 0; --newCol) {
        if (board[row][newCol] == nullptr) {
            possibleMoves.push_back(Coordinate(row, newCol));
        } else if (board[row][newCol]->getColour() != getColour()) {
            possibleMoves.push_back(Coordinate(row, newCol));
	        break;
        } else {
            break;
        }
    }
}
/*

vector<Coordinate> Rook::getAllAttackMoves(ChessPiece* board[8][8]) const {
    // Implement the Rook's attack moves logic here
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
void Rook::getAllCheckMoves(ChessPiece* board[8][8]) {

    checkMoves.clear();
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Rook temp(move, tempCol);
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
void Rook::adjustPossibleMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> tempMoves;
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Rook temp(move, tempCol);
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

