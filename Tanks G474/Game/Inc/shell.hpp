#pragma once

#include "entity.hpp"
#include "config.hpp"

#define SHELL_LENGTH 3

class Shell: public Entity {
public:

int prew_x;
int prew_y;
bool life = true;
Shell(int x, int y, int dir, int side);

void move();
void update();
void print();

~Shell();
};
