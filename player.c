#include "player.h"

#include "global.h"

void init_player(ent_player* p){
    p->x = 0; p->y = 0;
    p->vx = 0; p->vy = 0;
    p->isAttract = -1;
}

void input_player(ent_player* p){
    Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
    if(currentKeyState[SDL_SCANCODE_W]) p->vy = -PLAYER_VELOCITY;
    if(currentKeyState[SDL_SCANCODE_S]) p->vy = PLAYER_VELOCITY;
    if(currentKeyState[SDL_SCANCODE_A]) p->vx = -PLAYER_VELOCITY;
    if(currentKeyState[SDL_SCANCODE_D]) p->vx = PLAYER_VELOCITY;
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(SDL_BUTTON_LEFT)) p->isAttract = 1;
    else if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(SDL_BUTTON_RIGHT)) p->isAttract = -1;
    else p->isAttract = 0;
}

void update_player(ent_player* p){
    if(p->vx > 0){
        p->vx-=FRICTION_LEVEL*deltaTime;
        if(p->vx < 0){
            p->vx = 0;
        }
    }
    if(p->vx < 0){
        p->vx+=FRICTION_LEVEL*deltaTime;
        if(p->vx > 0){
            p->vx = 0;
        }
    }
    if(p->vy > 0){
        p->vy-=FRICTION_LEVEL*deltaTime;
        if(p->vy < 0){
            p->vy = 0;
        }
    }
    if(p->vy < 0){
        p->vy+=FRICTION_LEVEL*deltaTime;
        if(p->vy > 0){
            p->vy = 0;
        }
    }
    p->x+=p->vx*deltaTime;
    int checkC = 0;
    int x = p->x, y = p->y;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(worldCollision[x+i][y+j] == 1){
                checkC = 1;
            }
        }
    }
    if(checkC) p->x-=p->vx*deltaTime;
    checkC = 0;
    p->y+=p->vy*deltaTime;
    x = p->x; y = p->y;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(worldCollision[x+i][y+j] == 1){
                checkC = 1;
            }
        }
    }
    if(checkC) p->y-=p->vy*deltaTime;
}

void render_playerTop(ent_player* p){
    SDL_Rect box = {(p->x-offsetX)*TILE_SIZE, (p->y-offsetY)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderFillRect(render, &box);
}

void render_playerBottom(ent_player* p){
    SDL_Rect box = {(p->x-offsetX)*TILE_SIZE, (p->y-offsetY+1)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderFillRect(render, &box);
}
