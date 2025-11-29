#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include <Arduboy2.h>
#include "tangram_pieces.h"

// Объявления функций экранов
void drawMainMenu();
void handleMainMenuInput();
void drawLevelSelection();
void handleLevelSelectionInput();
void drawGameScreen();
void handleGameInput();
void drawSandboxScreen();
void handleSandboxInput();

// Вспомогательные функции
void drawTargetArea();
void drawGameField();
void drawCurrentPieceArea();
void drawControlsHelp();
void drawTargetShape(int x, int y);
void drawPieceInfo();
void loadLevel(int level);

#endif