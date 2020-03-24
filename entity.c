#include "entity.h"

#include "global.h"
#include "player.h"

#include "basicfunc.h"

#include <math.h>

prop_dynamic create_prop(double x, double y, double w, double h, int num_texture){
    prop_dynamic p = {x, y, 0, 0, w, h, num_texture};
    return p;
}

void render_prop(prop_dynamic* p){
    SDL_Rect box = {(p->x-offsetX)*TILE_SIZE, (p->y-offsetY)*TILE_SIZE, p->w*TILE_SIZE, p->h*TILE_SIZE};
    SDL_RenderCopy(render, prop_pack[p->num_texture], NULL, &box);
    //SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
    //SDL_RenderFillRect(render, &box);
}

void update_prop(prop_dynamic* p){
    double dist = distSquared(p->x, p->y, mainPlayer.x, mainPlayer.y);
    double angle = atan2(p->y-mainPlayer.y, p->x-mainPlayer.x);
    if(dist < MAX_RADIUS_ATTRACTION*MAX_RADIUS_ATTRACTION && mainPlayer.isAttract != 0){
        if(mainPlayer.isAttract == 1){
            p->vx = cos(angle)*30;
            p->vy = sin(angle)*30;
        }
        else{
            p->vx = -cos(angle)*8;
            p->vy = -sin(angle)*8;
        }
    }
    int checkC = 0;
    p->x+=p->vx*deltaTime;
    for(int i = 0; i < p->w+1; i++){
        for(int j = 0; j < p->h+1; j++){
            if(worldCollision[i+(int)p->x][j+(int)p->y]){
                SDL_Rect currentBlock = {(i+(int)p->x)*TILE_SIZE, (j+(int)p->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_Rect hitbox = {p->x*TILE_SIZE, p->y*TILE_SIZE, p->w*TILE_SIZE, p->h*TILE_SIZE};
                if(checkCollision(currentBlock, hitbox)){
                    p->x-=p->vx*deltaTime;
                    checkC = 1;
                    break;
                }
            }
        }
        if(checkC) break;
    }
    checkC = 0;
    p->y+=p->vy*deltaTime;
    for(int i = 0; i < p->w+1; i++){
        for(int j = 0; j < p->h+1; j++){
            if(worldCollision[i+(int)p->x][j+(int)p->y]){
                SDL_Rect currentBlock = {(i+(int)p->x)*TILE_SIZE, (j+(int)p->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_Rect hitbox = {p->x*TILE_SIZE, p->y*TILE_SIZE, p->w*TILE_SIZE, p->h*TILE_SIZE};
                if(checkCollision(currentBlock, hitbox)){
                    p->y-=p->vy*deltaTime;
                    checkC = 1;
                    break;
                }
            }
        }
        if(checkC) break;
    }
    double velAngle = atan2(p->vy, p->vx);
    double accx = FRICTION_LEVEL_PROPS*deltaTime*cos(velAngle);
    double accy = FRICTION_LEVEL_PROPS*deltaTime*sin(velAngle);
    if(p->vx > 0){
        p->vx -= accx;
        if(p->vx < 0){
            p->vx = 0;
        }
    }
    if(p->vx < 0){
        p->vx -= accx;
        if(p->vx > 0){
            p->vx = 0;
        }
    }
    if(p->vy > 0){
        p->vy -= accy;
        if(p->vy < 0){
            p->vy = 0;
        }
    }
    if(p->vy < 0){
        p->vy -= accy;
        if(p->vy > 0){
            p->vy = 0;
        }
    }
}
