#include "world.h"

#include "global.h"
#include "entity.h"

#include "basicfunc.h"

#include <stdio.h>
#include <stdlib.h>

void load_world(char* levelName){
    for(int i = 0; i < MAX_WORLD_SIZE; i++){
        for(int j = 0; j < MAX_WORLD_SIZE; j++){
            worldCollision[i][j] = 0;
            worldTextureBackground[i][j] = -1;
            worldTextureForeground[i][j] = -1;
        }
    }
    FILE* level;
    level = fopen(levelName, "r");
    if(level != NULL){
        int numOfTextures;
        fscanf(level, "%i", &numOfTextures);
        for(int i = 0; i < numOfTextures; i++){
            char currentTexture[256];
            fscanf(level, "%s", currentTexture);
            texture_pack[i] = loadTexture(currentTexture);
        }
        int numOfTexturesProp;
        fscanf(level, "%i", &numOfTexturesProp);
        for(int i = 0; i < numOfTexturesProp; i++){
            char currentProp[256];
            fscanf(level, "%s", currentProp);
            prop_pack[i] = loadTexture(currentProp);
        }
        int numOfCollisions;
        fscanf(level, "%i", &numOfCollisions);
        for(int i = 0; i < numOfCollisions; i++){
            int x, y;
            fscanf(level, "%i %i", &x, &y);
            if(x >= 0 && y >= 0 && x < MAX_WORLD_SIZE && y < MAX_WORLD_SIZE){
                worldCollision[x][y] = 1;
            }
        }
        int numOfForegroundBlocks;
        fscanf(level, "%i", &numOfForegroundBlocks);
        for(int i = 0; i < numOfForegroundBlocks; i++){
            int x, y, z;
            fscanf(level, "%i %i %i", &x, &y, &z);
            if(x >= 0 && y >= 0 && x < MAX_WORLD_SIZE && y < MAX_WORLD_SIZE){
                worldTextureForeground[x][y] = z;
            }
        }
        int numOfBackgroundBlocks;
        fscanf(level, "%i", &numOfBackgroundBlocks);
        for(int i = 0; i < numOfBackgroundBlocks; i++){
            int x, y, z;
            fscanf(level, "%i %i %i", &x, &y, &z);
            if(x >= 0 && y >= 0 && x < MAX_WORLD_SIZE && y < MAX_WORLD_SIZE){
                worldTextureBackground[x][y] = z;
            }
        }
        int numOfProps;
        fscanf(level, "%i", &numOfProps);
        maxProps = numOfProps;
        listOfProps = malloc(numOfProps*sizeof(prop_dynamic));
        for(int i = 0; i < numOfProps; i++){
            float x, y, w, h; int texture;
            fscanf(level, "%f %f %f %f %i", &x, &y, &w, &h, &texture);
            *(listOfProps+i) = create_prop(x, y, w, h, texture);
        }
        int numOfEnemies;
        fscanf(level, "%i", &numOfProps);
        for(int i = 0; i < numOfEnemies; i++){
            int type, x, y;
            // to be worked
        }
        fclose(level);
    }
}

void render_world(){
    for(int i = 0; i < offsetX+NUM_TILES_X+1; i++){
        for(int j = 0; j < offsetY+NUM_TILES_Y+1; j++){
            if(worldTextureForeground[i][j] != -1){
                //printf("%i %i\n", i, j);
                SDL_Rect box = {(i-offsetX)*TILE_SIZE, (j-offsetY)*TILE_SIZE, TILE_SIZE, 2*TILE_SIZE};
                //SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                //SDL_RenderFillRect(render, &box);
                //box.y+=TILE_SIZE;
                //SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
                //SDL_RenderFillRect(render, &box);
                int texture = worldTextureForeground[i][j];
                SDL_RenderCopy(render, texture_pack[texture], NULL, &box);
            }
        }
    }
}
