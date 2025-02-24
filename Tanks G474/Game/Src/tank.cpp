#include "list"
#include <math.h>
#include "tank.hpp"
#include "st7789.h"
#include <tank_frames.hpp>
#include "shell.hpp"
#include "config.hpp"

Tank::Tank(int x, int y, int dir, int side) : Entity(x, y, dir, side), frame_buff(
    (side == 0) ? tank_ally_frames : tank_enemy_frames)
{
  this->frame = 0;
  this->frame_buff_directed = frame_buff[this->dir];
}

void Tank::move()
{
  action = MOVE;
  ch_dir_cd += 1;
  
  switch (dir) {
    case UP:
      y -= 1;
      break;
    case DOWN:
      y += 1;
      break;
    case LEFT:
      x -= 1;
      break;
    case RIGHT:
      x += 1;
      break;
  }
  
  if (x < 6) {
    x = 6;
    action = BLOCK;
    stuck_cnt += 1;
  }
  else if (x > (FIELD_WIDTH - 1 - 6)) {
    x = FIELD_WIDTH - 1 - 6;
    action = BLOCK;
    stuck_cnt += 1;
  }
  
  if (y < 6) {
    y = 6;
    action = BLOCK;
    stuck_cnt += 1;
  }
  else if (y > (FIELD_HEIGHT - 1 - 6)) {
    stuck_cnt += 1;
    y = FIELD_HEIGHT - 1 - 6;
    action = BLOCK;
  }
  
  frame = (frame + 1) % FRAMES;
}

void Tank::back(bool stuck)
{
  
  switch (dir) {
    case UP:
      y += 1;
      break;
    case DOWN:
      y -= 1;
      break;
    case LEFT:
      x += 1;
      break;
    case RIGHT:
      x -= 1;
      break;
  }
  
  if (stuck) {
    stuck_cnt += (stuck_cnt < 10) ? 1 : 0;
    action = BLOCK;
  }
}

void Tank::rotate(int new_dir = false)
{
  dir = (new_dir % 4);
  frame_buff_directed = frame_buff[dir];
  action = ROTATE;
}

void Tank::update()
{
  if ((ch_dir_cd > 100) || (stuck_cnt > 3)) {
    if ((rand() % 4096) > 3700) {
      stuck_cnt = 0;
      ch_dir_cd = 0;
      int new_dir = dir + (rand() % 3) + 1;
      rotate(new_dir);
    }
  }
  else
    ch_dir_cd += 1;
  
  move();
  
  if (shot_cd >= 60) {
    if ((rand() / 4096) > 3900) {
      shot_cd = 0;
      shot_st = true;
    }
  }
  else
    shot_cd += 1;
}

void Tank::shot(std::list<Shell*> &shells)
{
  if (!shot_st)
    return;
  
  shot_st = false;
  
  int x_shot = x;
  int y_shot = y;
  
  switch (dir) {
    case UP:
      y_shot -= (TANK_HEIGHT / 2) + SHELL_LENGTH / 2 + 1;
      break;
    case DOWN:
      y_shot += (TANK_HEIGHT / 2) + SHELL_LENGTH / 2 + 1;
      break;
    case LEFT:
      x_shot -= (TANK_WIDTH / 2) + SHELL_LENGTH / 2 + 1;
      break;
    case RIGHT:
      x_shot += (TANK_WIDTH / 2) + SHELL_LENGTH / 2 + 1;
      break;
  }
  
  if (x_shot < SHELL_LENGTH / 2)
    return;
  if (x_shot > FIELD_WIDTH + (SHELL_LENGTH / 2))
    return;
  
  if (y_shot < SHELL_LENGTH / 2)
    return;
  if (y_shot > FIELD_HEIGHT + (SHELL_LENGTH / 2))
    return;
  
  shells.push_back(new Shell(x_shot, y_shot, dir, side));
}

void Tank::print()
{
  if (action == MOVE)
    switch (dir) {
      case UP:
        ST7789_DrawLine(x - 6, y + 7, x + 6, y + 7, BLACK);
        break;
      case DOWN:
        ST7789_DrawLine(x - 6, y - 7, x + 6, y - 7, BLACK);
        break;
      case LEFT:
        ST7789_DrawLine(x + 7, y - 6, x + 7, y + 6, BLACK);
        break;
      case RIGHT:
        ST7789_DrawLine(x - 7, y - 6, x - 7, y + 6, BLACK);
        break;
    }
  
  ST7789_DrawImage(x - 6, y - 6, 13, 13, frame_buff_directed[frame]);
}

Tank::~Tank()
{
  if (action == MOVE)
    switch (dir) {
      case UP:
        ST7789_DrawLine(x - 6, y + 7, x + 6, y + 7, BLACK);
        break;
      case DOWN:
        ST7789_DrawLine(x - 6, y - 7, x + 6, y - 7, BLACK);
        break;
      case LEFT:
        ST7789_DrawLine(x + 7, y - 6, x + 7, y + 6, BLACK);
        break;
      case RIGHT:
        ST7789_DrawLine(x - 7, y - 6, x - 7, y + 6, BLACK);
        break;
    }
  ST7789_DrawImage(x - 6, y - 6, 13, 13, tank_clear);
}
