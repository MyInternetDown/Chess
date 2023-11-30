#include <iostream>
#include <string>
#include "board.h"
using namespace std;


int main() {
  string cmd, aux;

  // You will need to make changes this code.

  while (true) {
    cin >> cmd;
    if (cmd == "game") {
      string player1, player2;
      cin >> player1 >> player2;
      //init game
    }
    else if (cmd == "resign") {
      //end game
    }
    else if (cmd == "move") {
      //first check computer

      string moveAt, moveTo;
      cin >> moveAt >> moveTo;
    }
    else if (cmd == "setup") {
      string cmd2;
      while (true) {
        cin >> cmd2;
        if (cmd2 == "done") {
          break; //done setup
        } else if (cmd2 == "+") {
          string piece, location;
          cin >> piece >> location;
          //move piece to location
        } else if (cmd2 == "-") {
          string location;
          cin >> location;
          //remove piece at location
        } else if (cmd2 == "=") {
          string colour;
          cin >> colour;
          //switch piece to colour
        }


      }
    }
  }
}
