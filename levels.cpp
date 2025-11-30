#include "levels.h"
#include <Arduboy2.h>

extern Arduboy2 arduboy;

const int silhouetteX = 15;
const int silhouetteY = 15;
const int silhouetteWidth = 70;
const int silhouetteHeight = 40;
const int TOTAL_LEVELS = 8;

void drawAlpakaSilhouette();
void drawArrowSilhouette();
void drawTreeSilhouette();
void drawDefaultSilhouette(int level);

void drawLevelSilhouette(int level) {
  
  // Рисуем силуэт уровня примитивами
  switch(level) {
    case 0: // Уровень 1 - альпака
      drawAlpakaSilhouette();
      break;
    case 1: // Уровень 2 - Стрелка
      drawArrowSilhouette();
      break;
    case 2: // Уровень 3 - Елочка
      drawTreeSilhouette();
      break;
    default:
      // Для остальных уровней - заглушка
      drawDefaultSilhouette(level);
      break;
  }
}

// Уровень 1: Силуэт альпаки
void drawAlpakaSilhouette() {
  int x = silhouetteX;
  int y = silhouetteY;
  
  // Основной контур тела альпаки
  // Спина и шея
  arduboy.drawLine(x + 65, y + 25, x + 35, y + 25, WHITE);
  arduboy.drawLine(x + 35, y + 25, x + 35, 25, WHITE);
  //arduboy.drawLine(x + 30, y + 15, x + 35, y + 10, WHITE);

  // Уши
  arduboy.drawLine(x + 34, 25, x + 34, 23, WHITE);
  arduboy.drawLine(x + 34, 23, x + 32, 20, WHITE);
  arduboy.drawLine(x + 32, 20, x + 32, 25, WHITE);

  arduboy.drawLine(x + 32, 25, x + 28, 25, WHITE);

  arduboy.drawLine(x + 28, 25, x + 28, 25, WHITE);
  arduboy.drawLine(x + 28, 25, x + 26, 22, WHITE);
  arduboy.drawLine(x + 26, 22, x + 26, 27, WHITE);

  // Голова
  arduboy.drawLine(x + 26, 27, x + 24, y + 15, WHITE);
  arduboy.drawLine(x + 24, y + 15, x + 24, y + 17, WHITE);
  arduboy.drawLine(x + 24, y + 17, x + 28, y + 17, WHITE);
  
  // Шея и грудь
  arduboy.drawLine(x + 28, y + 17, x + 28, y + 28, WHITE);
  arduboy.drawLine(x + 28, y + 28, x + 35, y + 34, WHITE);

  // Ноги
  // Передние
  arduboy.drawLine(x + 35, y + 34, x + 35, y + 40, WHITE);
  arduboy.drawLine(x + 35, y + 40, x + 38, y + 40, WHITE);
  arduboy.drawLine(x + 38, y + 40, x + 38, y + 34, WHITE);

  arduboy.drawLine(x + 40, y + 34, x + 40, y + 40, WHITE);
  arduboy.drawLine(x + 40, y + 40, x + 43, y + 40, WHITE);
  arduboy.drawLine(x + 43, y + 40, x + 43, y + 34, WHITE);
  
  // Задние
  arduboy.drawLine(x + 50, y + 34, x + 50, y + 40, WHITE);
  arduboy.drawLine(x + 50, y + 40, x + 53, y + 40, WHITE);
  arduboy.drawLine(x + 53, y + 40, x + 53, y + 34, WHITE);

  arduboy.drawLine(x + 55, y + 34, x + 55, y + 40, WHITE);
  arduboy.drawLine(x + 55, y + 40, x + 58, y + 40, WHITE);
  arduboy.drawLine(x + 58, y + 40, x + 58, y + 34, WHITE);
  
  // Живот
  arduboy.drawLine(x + 38, y + 34, x + 40, y + 34, WHITE);
  arduboy.drawLine(x + 43, y + 34, x + 50, y + 34, WHITE);
  arduboy.drawLine(x + 58, y + 34, x + 60, y + 34, WHITE);
  arduboy.drawLine(x + 60, y + 34, x + 62, y + 30, WHITE);
  
  // Хвост
  arduboy.drawLine(x + 62, y + 30, x + 65, y + 30, WHITE);
  arduboy.drawLine(x + 65, y + 30, x + 65, y + 25, WHITE);
}

// Уровень 2: Стрелка
void drawArrowSilhouette() {
  int x = silhouetteX;
  int y = silhouetteY;
  
  // Основа стрелки
  arduboy.drawRect(x + 25, y + 15, 20, 10, WHITE);
  
  // Наконечник
  arduboy.drawTriangle(x + 45, y + 15, 
                      x + 55, y + 20, 
                      x + 45, y + 25, WHITE);
}

// Уровень 3: Елочка
void drawTreeSilhouette() {
  int x = silhouetteX;
  int y = silhouetteY;
  
  // Ярусы елки
  arduboy.drawTriangle(x + 35, y + 10, x + 25, y + 20, x + 45, y + 20, WHITE);
  arduboy.drawTriangle(x + 35, y + 15, x + 20, y + 30, x + 50, y + 30, WHITE);
  arduboy.drawTriangle(x + 35, y + 25, x + 15, y + 40, x + 55, y + 40, WHITE);
  
  // Ствол
  arduboy.drawRect(x + 32, y + 40, 6, 5, WHITE);
}

// Заглушка для остальных уровней
void drawDefaultSilhouette(int level) {
  arduboy.setCursor(silhouetteX + 20, silhouetteY + 15);
  arduboy.print("LEVEL ");
  arduboy.print(level + 1);
}