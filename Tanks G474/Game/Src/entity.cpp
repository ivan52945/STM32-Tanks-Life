#include "entity.hpp"

Entity::Entity(int x, int y, int dir, int side)
{
  this->x = x;
  this->y = y;
  this->side = side;
  this->dir = dir;
}

Entity::~Entity() { }
