#include "enum.h"
using namespace std;

map<Colour, string> colourToStr = {
    {Colour::Void, "NoColour"},
    {Colour::Black, "Black"},
    {Colour::White, "White"}
};

map<string, Colour> strToColour = {
    { "NoColour", Colour::Void },
    { "Black", Colour::Black },
    { "White", Colour::White }
};

map<char, PieceType> charToPiece = {
    { 'P', PieceType::P },
    { 'B', PieceType::B },
    { 'N', PieceType::N },
    { 'R', PieceType::R },
    { 'Q', PieceType::Q },
    { 'K', PieceType::K },
    { 'V', PieceType::V }
};

map<string, PieceType> strToPiece = {
    { "P", PieceType::P },
    { "B", PieceType::B },
    { "N", PieceType::K },
    { "R", PieceType::R },
    { "Q", PieceType::Q },
    { "K", PieceType::K },
    { "V", PieceType::V }
};
