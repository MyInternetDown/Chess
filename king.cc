// king.cc

#include "king.h"

King::King(string pos, string white)
    : ChessPiece(pos, white, "K"), hasMoved(false) {  // Initialize hasMoved to false
    // You can add additional initialization for the King if needed
}

vector<Coordinate> King::getAllMoves(const Coordinate position, const vector<vector<ChessPiece>> &board) const{
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
            (board[newRow][newCol].isEmpty() || board[newRow][newCol].getColour() != getColour())) {
            moves.push_back({newRow, newCol});
        }
    }

    
    // castling
    if (!hasMoved) {
        if (board[row][0].getPiece() == PieceType::R && board[row][0].getColour() == getColour()
        && board[row][0].moved();
        ) {

        }

        if (board[row][7].getPiece() == PieceType::R && board[row][7].getColour() == getColour()
        && board[row][7].moved()) {

        }
    }


    return moves;
}

bool King::moved() {
    return hasMoved;
}
