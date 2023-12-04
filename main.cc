#include <iostream>
#include <string>
#include "board.h"
#include <cctype> 
#include <cstdlib>
using namespace std;


int main() {
  srand(time(0));
  string cmd, aux;
  Board game;
  // You will need to make changes this code.
  int point1, point2 = 0;

  while (true) {
    cin >> cmd;
    if (cmd == "game") {
      string player1, player2;
      cin >> player1 >> player2;
      game.create(player1, player2);
    }
    else if (cmd == "resign") {
      if(game.getTurn() == true) {
        point2++;
      } else {
        point1++;
      }
      game.reset();
    }
    else if (cmd == "move") {
      if ((game.player1 == H && game.getTurn())
        ||(game.player2 == H && !game.getTurn())) {
        string moveAt, moveTo;
        cin >> moveAt >> moveTo;
        cerr << moveAt << " " << moveTo << endl;
        game.humanMove(moveAt, moveTo);
      } else {
        game.move();
      }
    }
    else if (cmd == "setup") {
      string cmd2;
      cerr << "setup enter" << endl;
      while (true) {
        cin >> cmd2;
        if (cmd2 == "done") {
          cerr << "done" << endl;
          if (game.isValidSetup()) {
            game.updatePieces();
            break;
          }
        } else if(cmd2 == "default") {
          game.defaultSetup();
        }
        else if (cmd2 == "+") {
          string piece, location, colour;
          cin >> piece >> location;
          cerr << "input ...................... " << endl;
          cerr << piece << endl;
          cerr << location << endl;
          
          // Infer color based on the case of the type
          if (std::isupper(piece[0])) {
              colour = "White";
          } else {
              colour = "Black";
          }
          cerr << "check again" << endl;

          try {
            cerr << piece << endl;
            game.init(location, piece, colour);
            cerr << "hel" << endl;
          } catch (const std::invalid_argument &e) {
              std::cerr << "Error: " << e.what() << std::endl;
          }
          //move piece to location
        } else if (cmd2 == "-") {
          string location;
          cin >> location;
          Coordinate coord;
          istringstream pos(location);
          pos >> coord;
          game.removePiece(coord, false);
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
