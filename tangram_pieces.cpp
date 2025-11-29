#include "tangram_pieces.h"
#include "constants.h"

extern Arduboy2 arduboy;

void drawTangramPiece(int x, int y, int pieceType, int rotation) {
  switch(pieceType) {
    case BIG_TRIANGLE_1:
      arduboy.drawTriangle(x, y, x+12, y, x, y+12, WHITE);
      break;
    case BIG_TRIANGLE_2:
      arduboy.drawTriangle(x, y, x+12, y, x+12, y+12, WHITE);
      break;
    case MEDIUM_TRIANGLE:
      arduboy.drawTriangle(x, y, x+10, y, x, y+10, WHITE);
      break;
    case SMALL_TRIANGLE_1:
      arduboy.drawTriangle(x, y, x+8, y, x, y+8, WHITE);
      break;
    case SMALL_TRIANGLE_2:
      arduboy.drawTriangle(x, y, x+8, y, x+8, y+8, WHITE);
      break;
    case SQUARE:
      arduboy.drawRect(x, y, 8, 8, WHITE);
      break;
    case PARALLELOGRAM:
      arduboy.drawLine(x, y, x+10, y, WHITE);
      arduboy.drawLine(x+10, y, x+12, y+6, WHITE);
      arduboy.drawLine(x+12, y+6, x+2, y+6, WHITE);
      arduboy.drawLine(x+2, y+6, x, y, WHITE);
      break;
  }
}

void drawSmallTangramPiece(int x, int y, int pieceType, int rotation) {
  switch(pieceType) {
    case BIG_TRIANGLE_1:
      arduboy.drawTriangle(x, y, x+6, y, x, y+6, WHITE);
      break;
    case BIG_TRIANGLE_2:
      arduboy.drawTriangle(x, y, x+6, y, x+6, y+6, WHITE);
      break;
    case MEDIUM_TRIANGLE:
      arduboy.drawTriangle(x, y, x+5, y, x, y+5, WHITE);
      break;
    case SMALL_TRIANGLE_1:
      arduboy.drawTriangle(x, y, x+4, y, x, y+4, WHITE);
      break;
    case SMALL_TRIANGLE_2:
      arduboy.drawTriangle(x, y, x+4, y, x+4, y+4, WHITE);
      break;
    case SQUARE:
      arduboy.drawRect(x, y, 4, 4, WHITE);
      break;
    case PARALLELOGRAM:
      arduboy.drawLine(x, y, x+5, y, WHITE);
      arduboy.drawLine(x+5, y, x+6, y+3, WHITE);
      arduboy.drawLine(x+6, y+3, x+1, y+3, WHITE);
      arduboy.drawLine(x+1, y+3, x, y, WHITE);
      break;
  }
}

int getPieceWidth(int pieceType, int rotation) {
  switch(pieceType) {
    case BIG_TRIANGLE_1: case BIG_TRIANGLE_2: return 12;
    case MEDIUM_TRIANGLE: return 10;
    case SMALL_TRIANGLE_1: case SMALL_TRIANGLE_2: case SQUARE: return 8;
    case PARALLELOGRAM: return 12;
    default: return 8;
  }
}

int getPieceHeight(int pieceType, int rotation) {
  switch(pieceType) {
    case BIG_TRIANGLE_1: case BIG_TRIANGLE_2: return 12;
    case MEDIUM_TRIANGLE: return 10;
    case SMALL_TRIANGLE_1: case SMALL_TRIANGLE_2: case SQUARE: return 8;
    case PARALLELOGRAM: return 6;
    default: return 8;
  }
}