#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"

class Board;

class GraphicsDisplay: public Observer {
  std::vector<std::vector<int>> theDisplay;
  Xwindow *winFrame;
  const int gridSize;
 public:
  GraphicsDisplay(Xwindow *winFrame, int n);
  
  void notify(char chessBoard[8][8]) override;
  SubscriptionType subType() override;
  
  ~GraphicsDisplay();
};

#endif
