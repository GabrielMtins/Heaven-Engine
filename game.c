#include "game.h"

#include "global.h"
#include "player.h"
#include "world.h"
#include "entity.h"

void init(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode DM;
    if(SDL_GetCurrentDisplayMode(0, &DM) != 0){
        return;
    }
    WINDOW_WIDTH = DM.w;
    WINDOW_HEIGHT = DM.h;
    window = SDL_CreateWindow("HeavenEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TILE_SIZE = WINDOW_WIDTH/NUM_TILES_X;
    init_player(&mainPlayer);
    offsetX = 0;
    offsetY = 0;
    worldCollision[3][3] = 1;
    for(int i = 0; i < 12; i++) worldCollision[i][3] = 1;
    for(int i = 3; i < 24; i++) worldCollision[14][i] = 1;
    tile_texture = SDL_CreateTextureFromSurface(render, SDL_LoadBMP("tile.bmp"));
    printf("bruh\n");
    load_world("level.nml");
}

void updateLogic(){
    input_player(&mainPlayer);
    update_player(&mainPlayer);
    for(int i = 0; i < maxProps; i++) update_prop(listOfProps+i);
    if(mainPlayer.x>NUM_TILES_X/2) offsetX = mainPlayer.x-NUM_TILES_X/2;
    if(mainPlayer.y>NUM_TILES_Y/2) offsetY = mainPlayer.y-NUM_TILES_Y/2;
}

void renderScene(){
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
    render_playerBottom(&mainPlayer);
    render_world();
    render_playerTop(&mainPlayer);
    for(int i = 0; i < maxProps; i++) render_prop(listOfProps+i);
    SDL_RenderPresent(render);
}

void gameLoop(){
    int quit = 0;
    SDL_Event e;
    while(!quit){
        Uint32 firstTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = 1;
        }
        updateLogic();
        renderScene();
        deltaTime = (double)(SDL_GetTicks()-firstTime)/1000;
    }
}

void game(){
    init();
    gameLoop();
    free(listOfProps);
}
