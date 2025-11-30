#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include <Arduboy2.h>
#include "tangram_pieces.h"
#include "levels.h"
#include "constants.h"

struct Cursor {
  int x, y;
  bool visible;
};

struct LevelState {
  int availablePieces[7];
  Cursor cursor;
};

struct GameState {
  int selectedPieceType; 
  int heldPieceIndex;    
  bool pieceGrabbed;
};

struct ButtonStates {
  unsigned long aPressStartTime;
  unsigned long bPressStartTime;
  bool aWasPressed;
  bool bWasPressed;
  bool aIsLongPress;
  bool bIsLongPress;
  unsigned long lastRotationTime;
  unsigned long placeStartTime;
  unsigned long cancelStartTime;
};

void drawMainMenu();
void handleMainMenuInput();
void drawLevelSelection();
void handleLevelSelectionInput();
void drawGameScreen();
void handleGameInput();
void drawSandboxScreen();
void handleSandboxInput();

void drawTargetArea();
void drawGameField();
void drawCurrentPieceArea();
void drawControlsHelp();
void drawTargetShape(int x, int y);
void drawPieceInfo();
void loadLevel(int level);

void handleNoPieceMode(ButtonStates& btnState);
void handleCursorMode(ButtonStates& btnState); 
void handlePieceInHandMode(ButtonStates& btnState);
void handleButtonTransitions(ButtonStates& btnState);

bool takePieceWithCursor();
void createNewPiece();
void rotatePiece(bool clockwise);
void placePiece();
void cancelPiece();
void toggleCursor();
void exitLevel();
void rotatePoint(int& x, int& y, int centerX, int centerY, int rotation);
bool isPointInTangramPiece(int x, int y, TangramPiece piece);

void drawInstructionScreen();
void handleInstructionInput();

#endif