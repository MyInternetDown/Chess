// king.cc

#include "king.h"

King::King(string pos, string white)
    : ChessPiece(pos, white, "K") {  // Initialize hasMoved to false
    // You can add additional initialization for the King if needed
}

vector<Coordinate> King::getAllMoves(const Coordinate position, ChessPiece* board[8][8]) {
    vector<Coordinate> moves;

    const int row = position.getRow();
    const int col = position.getCol();

    // King moves one square in any direction
    vector<pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},             {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto &move : kingMoves) {
        int newRow = row + move.first;
        int newCol = col + move.second;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (board[newRow][newCol] == nullptr || board[newRow][newCol]->getColour() != getColour())) {
            moves.push_back({newRow, newCol});
        }
    }

    
    // castling (but no checks yet)
    if (!hasMoved) {
        if (board[row][0]->getPiece() == PieceType::R && board[row][0]->getColour() == getColour()
        && !board[row][0]->moved() && board[row][col - 1] == nullptr && board[row][col - 2] == nullptr)
        {
            moves.push_back({row, col - 2});
        }

        if (board[row][7]->getPiece() == PieceType::R && board[row][7]->getColour() == getColour()
        && !board[row][7]->moved() && board[row][col + 1] == nullptr && board[row][col + 2] == nullptr) {
            moves.push_back({row, col + 2});
        }
    }


    return moves;
}


vector<Coordinate> King::getAllAttackMoves(const vector<Coordinate> moves, ChessPiece* board[8][8]) const {
    // to do
    vector<Coordinate> attackMoves;

    for (const auto &move : moves) {
        // Add move to attack moves if an opponent's piece is encountered
        if (board[move.getRow()][move.getCol()]->getColour() != getColour()) {
            attackMoves.push_back(move);
        }
    }

    return attackMoves;
}

bool King::isChecked(ChessPiece* board[8][8]) const {
    //to do
    return false;
}
