// rook.cc

#include "rook.h"

Rook::Rook(Coordinate pos, string white)
    : ChessPiece(pos, white, "R"){  // Initialize hasMoved to false
    // You can add additional initialization for the Rook if needed
}

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

vector<Coordinate> Rook::getAllCheckMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> checkMoves;

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getPiece() == K) {
            checkMoves.push_back(move);
        }
    }

    return checkMoves;
}

*/