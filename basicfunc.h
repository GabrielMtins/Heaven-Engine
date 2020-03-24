#ifndef BASICFUNC_H
#define BASICFUNC_H

#include "global.h"

SDL_Texture* loadTexture(char* string);

double distSquared(double x1, double y1, double x2, double y2);

int checkCollision(SDL_Rect a, SDL_Rect b);

#endif
