// bishop.cc

#include "bishop.h"
#include <iostream>

Bishop::Bishop(Coordinate pos, string white)
    : ChessPiece(pos, white, "B") {
    // You can add additional initialization for the Bishop if needed
}

void Bishop::getAllMoves(ChessPiece* board[8][8]) {
    // Implement the Bishop's move logic here
    possibleMoves.clear();

    // Bishop moves diagonally
    // Adding all possible diagonal moves for the Bishop

    const int row = location.getRow();
    const int col = location.getCol();

    // Possible diagonal moves relative to the current position
    vector<pair<int, int>> bishopMoves = {
        {-1, -1}, {-1, 1},
        {1, -1}, {1, 1}
    };

    for (const auto &move : bishopMoves) {
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

void Bishop::adjustPossibleMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> tempMoves;
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Bishop temp(move, tempCol);
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

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && board[i][j]->getPiece() == K && temp.getColour() == board[i][j]->getColour()) {
                    if (!board[i][j]->isChecked(board)) {
                        tempMoves.push_back(move);
                    }
                }
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
    possibleMoves = tempMoves;
}


void Bishop::getAllCheckMoves(ChessPiece* board[8][8]) {

    checkMoves.clear();
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        Bishop temp(move, tempCol);
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

void Bishop::getAllLevel4Moves(ChessPiece* board[8][8]) {
    level4Moves.clear();
    for (const auto &move : attackMoves) {
        string tempCol = colourToStr.find(colour)->second;
        Bishop temp(move, tempCol);
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
        Bishop temp(move, tempCol);
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
        Bishop temp(move, tempCol);
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