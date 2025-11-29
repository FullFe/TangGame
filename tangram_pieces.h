#ifndef TANGRAM_PIECES_H
#define TANGRAM_PIECES_H

#include <Arduboy2.h>

struct TangramPiece {
  int x, y;
  int shape;
  bool placed;
  int rotation;
};

// Объявления функций
void drawTangramPiece(int x, int y, int pieceType, int rotation);
void drawSmallTangramPiece(int x, int y, int pieceType, int rotation);
int getPieceWidth(int pieceType, int rotation);
int getPieceHeight(int pieceType, int rotation);

#endif