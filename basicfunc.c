#include "basicfunc.h"

#include "global.h"

SDL_Texture* loadTexture(char* string){
    SDL_Surface* surface = NULL;
    surface = SDL_LoadBMP(string);
    SDL_Texture* currentTexture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    return currentTexture;
}

double distSquared(double x1, double y1, double x2, double y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

int checkCollision(SDL_Rect a, SDL_Rect b){
    if(a.y+a.h <= b.y) return 0;
    if(a.y >= b.y+b.h) return 0;
    if(a.x+a.w <= b.x) return 0;
    if(a.x >= b.x+b.w) return 0;
    return 1;
}
