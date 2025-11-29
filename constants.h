#ifndef CONSTANTS_H
#define CONSTANTS_H

// Состояния экранов
enum ScreenState {
  MENU_SCREEN,
  LEVEL_SELECT_SCREEN, 
  GAME_SCREEN,
  SANDBOX_SCREEN
};

// Типы фигур танграма
enum PieceType {
  BIG_TRIANGLE_1 = 0,
  BIG_TRIANGLE_2 = 1,
  MEDIUM_TRIANGLE = 2,
  SMALL_TRIANGLE_1 = 3,
  SMALL_TRIANGLE_2 = 4,
  SQUARE = 5,
  PARALLELOGRAM = 6
};

// Размеры экрана
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

// Границы игрового поля
const int FIELD_X = 15;
const int FIELD_Y = 10;
const int FIELD_WIDTH = 55;
const int FIELD_HEIGHT = 30;

#endif