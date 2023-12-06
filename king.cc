// king.cc

#include "king.h"
#include <iostream>

King::King(Coordinate pos, string white)
    : ChessPiece(pos, white, "K") {  // Initialize hasMoved to false
    // You can add additional initialization for the King if needed
    checked = false;
}

// Get all possible moves for the King
void King::getAllMoves(ChessPiece* board[8][8]) {
    possibleMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction
    vector<pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},             {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
    getAllDangerPositions(board);
    for (const auto &move : kingMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (board[newRow][newCol] == nullptr || board[newRow][newCol]->getColour() != getColour())) {

            
            possibleMoves.push_back({newRow, newCol});
        }
    }

    for (const auto& coord : possibleMoves) {
        if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
            possibleMoves.push_back(coord);
        }
        
     }
    //cerr << "king" << endl;
    //printVector(possibleMoves);
    
    // Check for castling moves if the king hasn't moved
    if (!moved()) {
        if (col == 4 && board[row][0] != nullptr && board[row][0]->getPiece() == PieceType::R && board[row][0]->getColour() == getColour()
        && !board[row][0]->moved() && board[row][col - 1] == nullptr && board[row][col - 2] == nullptr)
        {
            possibleMoves.push_back({row, col - 2});
        }

        if (col == 4 && board[row][7] != nullptr && board[row][7]->getPiece() == PieceType::R && board[row][7]->getColour() == getColour()
        && !board[row][7]->moved() && board[row][col + 1] == nullptr && board[row][col + 2] == nullptr) {
            possibleMoves.push_back({row, col + 2});
        }
    }
    
}


void King::getAllPotentialMoves(ChessPiece* board[8][8]) {
    allPotentialMoves.clear();

    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction
    vector<pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},             {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
    getAllDangerPositions(board);
    for (const auto &move : kingMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (board[newRow][newCol] == nullptr || board[newRow][newCol]->getColour() != getColour() || board[newRow][newCol]->getColour() == getColour())) {

            
            allPotentialMoves.push_back({newRow, newCol});
        }
    }

    for (const auto& coord : possibleMoves) {
        if (std::find(dangerSquares.begin(), dangerSquares.end(), coord) == dangerSquares.end()) {
            allPotentialMoves.push_back(coord);
        }
        
     }
    //cerr << "king" << endl;
    //printVector(possibleMoves);
    
    // Check for castling moves if the king hasn't moved
    if (!moved()) {
        if (col == 4 && board[row][0] != nullptr && board[row][0]->getPiece() == PieceType::R && board[row][0]->getColour() == getColour()
        && !board[row][0]->moved() && board[row][col - 1] == nullptr && board[row][col - 2] == nullptr)
        {
            allPotentialMoves.push_back({row, col - 2});
        }

        if (col == 4 && board[row][7] != nullptr && board[row][7]->getPiece() == PieceType::R && board[row][7]->getColour() == getColour()
        && !board[row][7]->moved() && board[row][col + 1] == nullptr && board[row][col + 2] == nullptr) {
            allPotentialMoves.push_back({row, col + 2});
        }
    }
    
}

// Check if the King is in a checked state
bool King::isChecked(ChessPiece* board[8][8]) {
    bool found = false;
    checked = false;
    protectKing.clear();
    const int row = location.getRow();
    const int col = location.getCol();

    //cerr << "enter king moves" << endl;

    // King moves one square in any direction
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && !(i == row && j == col)) {

                //cerr << "found piece validating" << endl;
                for (const Coordinate &move: board[i][j]->allPotentialMoves) {
                    //cerr << board[i][j]->getCharType() << " ...." << move << endl;
                    if (location == move) {
                        found = true;
                        checked = true;
                        // Calculate and store the squares protecting the king
                        if (board[i][j]->getPiece() != N) {
                            int dx = row - i;
                            int dy = col - j;
                            int steps = std::max(std::abs(dx), std::abs(dy));

                            for (int k = 0; k < steps; ++k) {
                                int newX = i + k * dx / steps;
                                int newY = j + k * dy / steps;
                                protectKing.push_back(Coordinate(newX, newY));
                            }
                        }
                    }
                }
            }
        }
    }
    return found;
}

// Get all possible moves to get out of a checked state
void King::getAllCheckMoves(ChessPiece* board[8][8]) {
    checkMoves.clear();
    blockKing = evadeMoves;

}

// Get all squares that can block an attack on the king
void King::getAllBlockKing(vector<Coordinate> protectPos) {
    blockKing = evadeMoves;
    //printVector(blockKing);
    //cerr << "block" << endl;

}

// Adjust possible moves considering opponent's moves
void King::adjustPossibleMoves(ChessPiece* board[8][8]) {
    vector<Coordinate> tempMoves;
    for (const auto &move : possibleMoves) {
        /*
        if (getColour() == White) {
            cerr << move << "             - " << endl;
        }
        */
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        King temp(move, tempCol);
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

        // Check if the king is not in a checked state after the move
        //for (int i = 0; i < 8; ++i) {
            //for (int j = 0; j < 8; ++j) {
        //if (board[i][j] != nullptr && board[i][j]->getPiece() == K && temp.getColour() == board[i][j]->getColour()) {
        if (!board[move.getRow()][move.getCol()]->isChecked(board)) {
            tempMoves.push_back(move);
                //cerr << "push_back" << endl;
                //printVector(tempMoves);
        }
        //}
            //}
        //}

        // Restore the original state of the board
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
    possibleMoves.clear();
    possibleMoves = tempMoves;
    //printVector(possibleMoves);
    //cerr << "adjust" << endl;
}

void King::getAllLevel4Moves(ChessPiece* board[8][8]) {
    for (const auto &move : possibleMoves) {
        // Add move to attack moves if an opponent's piece is encountered
        string tempCol = colourToStr.find(colour)->second;
        King temp(move, tempCol);
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


// Function to print the contents of a vector of Coordinates
void printVector(const std::vector<Coordinate>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}
