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
  SMALL_TRIANGLE_1 = 3,   // Для уровня 1: Квадрат 10px
  SMALL_TRIANGLE_2 = 4,   // Для уровня 1: Прямоугольник 5x10
  SQUARE = 5,             // Для уровня 1: Маленький квадрат 5x5
  PARALLELOGRAM = 6       
};

// Размеры экрана
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

// Границы игрового поля (весь экран под линией меню)
const int FIELD_X = 0;
const int FIELD_Y = 13;  
const int FIELD_WIDTH = 128;
const int FIELD_HEIGHT = 51; // 64 - 13 = 51

// Количество фигур для каждого уровня [уровень][тип_фигуры]
const int LEVEL_PIECES_COUNT[8][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // Уровень 1 - новые фигуры (все по 1 штуке)
  {2, 2, 1, 2, 2, 1, 1}, // Уровень 2 - стандартный набор
  {2, 0, 1, 0, 2, 1, 0}, // Уровень 3 - ограниченный набор
  {1, 1, 0, 2, 0, 1, 1}, // Уровень 4 - другой набор
  {0, 0, 2, 2, 2, 1, 0}, // Уровень 5 - только маленькие фигуры
  {2, 2, 0, 0, 0, 0, 1}, // Уровень 6 - только большие треугольники и параллелограмм
  {1, 0, 1, 1, 0, 1, 1}, // Уровень 7
  {0, 2, 1, 1, 1, 0, 1}  // Уровень 8
};

#endif