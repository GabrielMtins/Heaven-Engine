#ifndef ENTITY_H
#define ENTITY_H

typedef struct{
    double x, y;
    double vx, vy;
    double w, h;
    int num_texture;
} prop_dynamic;

prop_dynamic create_prop(double x, double y, double w, double h, int num_texture);

void render_prop(prop_dynamic* p);

void update_prop(prop_dynamic* p);

int maxProps;

prop_dynamic* listOfProps;

#endif
