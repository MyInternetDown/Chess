#include "enum.h"
using namespace std;

// Mapping from Colour enum to string representation
map<Colour, string> colourToStr = {
    {Colour::Void, "NoColour"},
    {Colour::Black, "Black"},
    {Colour::White, "White"}
};

// Mapping from string representation to Colour enum
map<string, Colour> strToColour = {
    { "NoColour", Colour::Void },
    { "Black", Colour::Black },
    { "White", Colour::White }
};

// Mapping from character representation to PieceType enum
map<char, PieceType> charToPiece = {
    { 'P', PieceType::P },
    { 'B', PieceType::B },
    { 'N', PieceType::N },
    { 'R', PieceType::R },
    { 'Q', PieceType::Q },
    { 'K', PieceType::K },
    { 'V', PieceType::V }
};

// Mapping from PieceType enum to character representation
map<PieceType, char> pieceToChar = {
    { PieceType::P, 'P' },
    { PieceType::B, 'B' },
    { PieceType::N, 'N' },
    { PieceType::R, 'R' },
    { PieceType::Q, 'Q' },
    { PieceType::K, 'K' },
    { PieceType::V, 'V' }
};

// Mapping from string representation to PieceType enum
map<string, PieceType> strToPiece = {
    { "P", PieceType::P },
    { "B", PieceType::B },
    { "N", PieceType::N },
    { "R", PieceType::R },
    { "Q", PieceType::Q },
    { "K", PieceType::K },
    { "V", PieceType::V }
};

// Mapping from string representation to MoveType enum
map<string, MoveType> strToMoveType = {
    {"human", H},
    {"computer1", L1},
    {"computer2", L2},
    {"computer3", L3},
    {"computer4", L4}
};

// Convert a string to MoveType enum
MoveType convertStringToMoveType(const std::string playerType) {
    auto it = strToMoveType.find(playerType);
    return it->second;
}

// Parse a string to a Colour enum
Colour parseColour(const std::string colorStr) {
    auto it = strToColour.find(colorStr);
    if (it != strToColour.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid color string");
}

// Parse a string to a PieceType enum
PieceType parsePieceType(const std::string typeStr) {
    auto it = strToPiece.find(typeStr);
    if (it != strToPiece.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid piece type string");
}

// Get the character representation from a PieceType enum
char getCharFromPieceType(PieceType piece) {
    auto it = pieceToChar.find(piece);
    if (it != pieceToChar.end()) {
        return it->second;
    }
    return ' ';  // Return a default value if not found
}
