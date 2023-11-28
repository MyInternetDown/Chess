#include <iostream>
#include <string>
#include "board.h"
using namespace std;

// This checks the edge case of one move left instead of moves
// takes in n which is moves from main and outputs based on the value
void getMoves(int n) {
  if (n == 1) {
    cout << n << " move left" << endl;
  }else{
    cout << n << " moves left" << endl;
  }
}

int main() {
  string cmd, aux;
  Grid g;
  int moves = 0;

  // You will need to make changes this code.

  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // initalizes the game
      g.init(n);
    }
    else if (cmd == "init") {
      int r, c;
      while(true) {
        cin >> r >> c;
        if (r == -1 && c == -1) break;
        g.turnOn(r, c);
      }
      cout << g;
    }
    else if (cmd == "game") {
      cin >> moves;
      getMoves(moves);
    }
    else if (cmd == "switch") {
      
      int r = 0, c = 0;
      cin >> r >> c;
      g.toggle(r, c);
      cout << g;
      --moves;
      // first removes the move then checks if they win or lose
      getMoves(moves);
      if (g.isWon()) {
        cout << "Won" << endl;
        break;
      }
      if (moves == 0) {
        cout << "Lost" << endl;
        break;
      } 
    }
  }
}
