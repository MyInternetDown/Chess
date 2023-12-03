#include <iostream>
#include <string>
#include "board.h"
#include <cctype> 
using namespace std;


int main() {
  string cmd, aux;
  Board game;
  // You will need to make changes this code.

  while (true) {
    cin >> cmd;
    if (cmd == "game") {
      string player1, player2;
      cin >> player1 >> player2;
      game.create(player1, player2);
    }
    else if (cmd == "resign") {
      // making it
    }
    else if (cmd == "move") {
      //first check compter

      string moveAt, moveTo;
      cin >> moveAt >> moveTo;
    }
    else if (cmd == "setup") {
      string cmd2;
      while (true) {
        cin >> cmd2;
        if (cmd2 == "done") {
          if (game.isValidSetup()) {
            break;
          }
        } else if (cmd2 == "+") {
          string piece, location, colour;
          cin >> piece >> location;
          char c;
          // Convert type to uppercase
          for (char &c : piece) {
            c = std::toupper(c);
          }
          string myString(1, c);

          // Infer color based on the case of the type
          if (std::isupper(piece[0])) {
            colour = "White";
        } else {
            colour = "Black";
        }

          try {
            game.init(location, myString, colour);
          } catch (const std::invalid_argument &e) {
              std::cerr << "Error: " << e.what() << std::endl;
          }
          //move piece to location
        } else if (cmd2 == "-") {
          string location;
          cin >> location;
          game.removePiece(location);
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
