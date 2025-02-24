#include "shell.hpp"
#include "st7789.h"

Shell::Shell(int x, int y, int dir, int side) : Entity(x, y, dir, side)
{
  this->prew_x = this->x;
  this->prew_y = this->y;
}

void Shell::move()
{
  switch (dir) {
    case UP:
      y -= 3;
      break;
    case DOWN:
      y += 3;
      break;
    case LEFT:
      x -= 3;
      break;
    case RIGHT:
      x += 3;
      break;
  }
  
  if (x < 1) {
    life = false;
  }
  else if (x > (FIELD_WIDTH - 1 - 1)) {
    life = false;
  }
  
  if (y < 1) {
    life = false;
  }
  else if (y > (FIELD_HEIGHT - 1 - 1)) {
    life = false;
  }
  
}

void Shell::update()
{
  move();
}

void Shell::print()
{
  if (!life)
    return;
  
  switch (dir) {
    case UP:
    case DOWN:
      ST7789_DrawLine(prew_x, prew_y - 1, prew_x, prew_y + 1, BLACK);
      ST7789_DrawLine(x, y - 1, x, y + 1, GRAY);
      break;
    case LEFT:
    case RIGHT:
      ST7789_DrawLine(prew_x - 1, prew_y, prew_x + 1, prew_y, BLACK);
      ST7789_DrawLine(x - 1, y, x + 1, y, GRAY);
      break;
  }
  prew_x = x;
  prew_y = y;
}

Shell::~Shell()
{
  /*
   if(prew_x < 1)
   return;
   if(prew_y < 1)
   return;

   if(prew_x > (FIELD_WIDTH - 1 - 1))
   return;
   if(prew_y > (FIELD_HEIGHT - 1 - 1))
   return;
   */

  switch (dir) {
    case UP:
    case DOWN:
      ST7789_DrawLine(prew_x, prew_y - 1, prew_x, prew_y + 1, BLACK);
      break;
    case LEFT:
    case RIGHT:
      ST7789_DrawLine(prew_x - 1, prew_y, prew_x + 1, prew_y, BLACK);
      break;
  }
}
