#ifndef ENUM_H
#define ENUM_H
#include <map>
#include <string>
#include <iostream>


using namespace std;

enum Colour { Void, Black, White };
enum PieceType { P='P', B='B', N='N', R='R', Q='Q', K='K', V='V'};
enum MoveType { H, L1, L2, L3, L4 };

extern map<Colour, std::string> colourToStr;
extern map<std::string, Colour> strToColour;
extern map<char, PieceType> charToPiece;
extern map<std::string, PieceType> strToPiece;
extern map<string, MoveType> strToMoveType;
Colour parseColour(const string colorStr);
PieceType parsePieceType(const string typeStr);
MoveType convertStringToMoveType(const std::string playerType);

#endif
