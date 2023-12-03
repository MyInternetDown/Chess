#include <iostream>
#include "graphicsdisplay.h"
#include "board.h"
using namespace std;

// Creates a new text display, resizes the vector for n slots each consisting of a vector of size n with 0. 
// Also makes black background
GraphicsDisplay::GraphicsDisplay(Xwindow *winFrame, int n) : gridSize(n), winFrame{winFrame}
{
 //  to do
}

// When notified, checks the cell and changes the value if it is on or off
// Then sets the colour accordingly
void GraphicsDisplay::notify(char chessBoard[8][8])
{
 // to do
}

GraphicsDisplay::~GraphicsDisplay() {}

SubscriptionType GraphicsDisplay::subType()
{
  return SubscriptionType::All;
}
