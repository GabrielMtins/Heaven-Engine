#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
    double x, y;
    double vx, vy;
    double isAttract;
} ent_player;

void init_player(ent_player* p);

void input_player(ent_player* p);

void update_player(ent_player* p);

void render_playerBottom(ent_player* p);

void render_playerTop(ent_player* p);

ent_player mainPlayer;

#endif
