#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"

// Forward declaration of the Board class
class Board;

class TextDisplay: public Observer {
  // 2D vector to represent the display of the chess board
  std::vector<std::vector<char>> theDisplay;
 public:
  // ctor
  TextDisplay();

  // update the display based on the board state
  void notify(char board[8][8]) override;
  // return the subscription type of the observer
  SubscriptionType subType() override;

  // dtor
  ~TextDisplay();

  // overload the << operator for easy output
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
