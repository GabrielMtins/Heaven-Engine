#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* render;

int TILE_SIZE;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

double deltaTime;

#define MAX_WORLD_SIZE 1024

int worldCollision[MAX_WORLD_SIZE][MAX_WORLD_SIZE];

int worldTextureBackground[MAX_WORLD_SIZE][MAX_WORLD_SIZE];

int worldTextureForeground[MAX_WORLD_SIZE][MAX_WORLD_SIZE];

#define FRICTION_LEVEL 70

#define FRICTION_LEVEL_PROPS 50

#define NUM_TILES_X 32

#define NUM_TILES_Y 18

#define PLAYER_VELOCITY 12

#define MAX_TEXTURE 256

#define PI 3.141592

#define MAX_RADIUS_ATTRACTION 10

SDL_Texture* player_texture;

SDL_Texture* texture_pack[MAX_TEXTURE];

SDL_Texture* tile_texture;

SDL_Texture* prop_pack[MAX_TEXTURE];

double offsetX, offsetY;

#endif
