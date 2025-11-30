#ifndef LEVELS_H
#define LEVELS_H

#include "constants.h"
#include <Arduboy2.h>

extern const int silhouetteX;
extern const int silhouetteY;
extern const int silhouetteWidth;
extern const int silhouetteHeight;

extern const int TOTAL_LEVELS;
void drawLevelSilhouette(int level);

#endif