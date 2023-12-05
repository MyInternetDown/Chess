#include <iostream>
#include "graphicsdisplay.h"
#include "board.h"
using namespace std;

// Creates a new text display, resizes the vector for n slots each consisting of a vector of size n with 0. 
// Also makes black background
GraphicsDisplay::GraphicsDisplay(Xwindow *winFrame) : winFrame{winFrame}, gridSize{8}
{
  for (int i = 0; i < gridSize; ++i) {
    vector<int> row;
    for (int j = 0; j < gridSize; ++j) {
      row.push_back(0); // Initialize theDisplay with 0
    }
    theDisplay.push_back(row);
  }

  // Set up the initial chessboard display
  for (int row = 0; row < gridSize; ++row){
    for (int col = 0; col < gridSize; ++col) {
      int color = (row + col) % 2 == 0 ? Xwindow::White : Xwindow::Green;
      winFrame->fillRectangle(col * 100, row * 100, 100, 100, color);
    }
  }
}

// When notified, checks the cell and changes the value if it is on or off
// Then sets the colour accordingly
void GraphicsDisplay::notify(char chessBoard[8][8])
{
  for (int row = 0; row < gridSize; ++row) {
    for (int col = 0; col < gridSize; ++col) {
      char piece = chessBoard[row][col];
      int color = (row + col) % 2 == 0 ? Xwindow::White : Xwindow::Green;
      int x = col * 100;
      int y = row * 100;

      // Clear the cell
      winFrame->fillRectangle(x, y, 100, 100, color);

      // Draw the piece, if any
      if (piece != ' ' && piece != '_') {
        // Additional logic here to determine the color and shape of the piece
        // based on the 'piece' variable, 
        //winFrame->fillRectangle(x + 25, y + 25, 50, 50, Xwindow::Red);
        string strPiece(1, piece);
        winFrame->drawString(x+25, y+25, strPiece);
      }
    }
  }
}

GraphicsDisplay::~GraphicsDisplay() {}

SubscriptionType GraphicsDisplay::subType()
{
  return SubscriptionType::All;
}
