#include <iostream>
#include "textdisplay.h"
#include "board.h"
using namespace std;

// Creates a new text display, resizes the vector for n slots each consisting of a vector of size n with '_'
TextDisplay::TextDisplay()
{
  theDisplay.resize(8, std::vector<char>(8, '_'));
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (i * 8 + j % 2 == 0) {
        theDisplay[i][j] = ' ';
      }
    }
  }
}


// When notified, checks the cell and changes the value if it is on or off
void TextDisplay::notify(char chessBoard[8][8])
{

}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::subType()
{
  return SubscriptionType::All;
}


// Goes through the display by the vector and prints out all the values
ostream &operator<<(ostream &out, const TextDisplay &td)
{
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  out << "  abcdefgh" << endl;
  return out;
}
