#include <iostream>
#include "textdisplay.h"
#include "board.h"
using namespace std;

// Creates a new text display, resizes the vector for n slots each consisting of a vector of size n with '_'
TextDisplay::TextDisplay()
{
  //theDisplay.resize(n, std::vector<char>(n, '_'));

}

/*
// When notified, checks the cell and changes the value if it is on or off
void TextDisplay::notify(Board &cb)
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
  for (int i = 0; i < td.gridSize; ++i)
  {
    for (int j = 0; j < td.gridSize; ++j)
    {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
*/