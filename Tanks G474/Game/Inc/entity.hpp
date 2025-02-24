#pragma once

enum side_t {
  UP, RIGHT, DOWN, LEFT,
};

class Entity {
public:
int x;
int y;
int side;
int dir;
//public:
Entity(int x, int y, int dir, int side);

//virtual void update() = 0;
virtual void print() = 0;

virtual ~Entity();
};
