// queen.cc

#include "queen.h"
#include <iostream>

Queen::Queen(Coordinate pos, string white)
    : ChessPiece(pos, white, "Q") {
    // You can add additional initialization for the Queen if needed
}

// Get all possible moves for the Queen
void Queen::getAllMoves(ChessPiece* board[8][8]) {
    // Implement the Queen's move logic here
    possibleMoves.clear();

    // Queen moves diagonally and linearly (horizontally and vertically)
    // Adding all possible moves for the Queen

    const int row = location.getRow();
    const int col = location.getCol();

    // Possible moves relative to the current position
    vector<pair<int, int>> queenMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : queenMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            // Check if the destination is empty or contains an opponent's piece
            if (board[newRow][newCol] == nullptr) {
                possibleMoves.push_back(Coordinate(newRow, newCol));
            } else if (board[newRow][newCol]->getColour() != getColour()) {
                possibleMoves.push_back(Coordinate(newRow, newCol));
                break;  // Stop if an opponent's piece is encountered
            } else {
                break;  // Stop if own piece is encountered
            }

            newRow += move.first;
            newCol += move.second;
        }
    }
}

void Queen::getAllPotentialMoves(ChessPiece* board[8][8]) {
    // Implement the Queen's move logic here
    allPotentialMoves.clear();

    // Queen moves diagonally and linearly (horizontally and vertically)
    // Adding all possible moves for the Queen

    const int row = location.getRow();
    const int col = location.getCol();

    // Possible moves relative to the current position
    vector<pair<int, int>> queenMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : queenMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            // Check if the destination is empty or contains an opponent's piece
            if (board[newRow][newCol] == nullptr) {
                allPotentialMoves.push_back(Coordinate(newRow, newCol));
            } else if (board[newRow][newCol]->getColour() != getColour() || board[newRow][newCol]->getColour() == getColour()) {
                allPotentialMoves.push_back(Coordinate(newRow, newCol));
                break;  // Stop if an opponent's piece is encountered
            } else {
                break;  // Stop if own piece is encountered
            }

            newRow += move.first;
            newCol += move.second;
        }
    }
}
/*
vector<Coordinate> Queen::getAllAttackMoves(ChessPiece* board[8][8]) const {
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
void Queen::getAllCheckMoves(ChessPiece* board[8][8]) {

    checkMoves.clear();
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Queen temp(move, tempCol);
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
void Queen::adjustPossibleMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> tempMoves;
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Queen temp(move, tempCol);
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

void Queen::getAllLevel4Moves(ChessPiece* board[8][8]) {
    level4Moves.clear();
    for (const auto &move : attackMoves) {
        string tempCol = colourToStr.find(colour)->second;
        Queen temp(move, tempCol);
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

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Queen temp(move, tempCol);
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

    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Queen temp(move, tempCol);
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
}
