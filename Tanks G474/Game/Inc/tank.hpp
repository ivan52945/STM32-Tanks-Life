#pragma once

#include "list"
#include "stdint.h"
#include <tank_frames.hpp>
#include "shell.hpp"
#include "entity.hpp"

#define TANK_WIDTH 13
#define TANK_HEIGHT 13

enum action_t {
  KIL, ROTATE, MOVE, BLOCK,
};

class Tank: public Entity {
private:
  int frame;

  int shot_cd = 0;
  const uint16_t (*frame_buff_directed)[HEIGHT * WIDTH];
  const uint16_t (*const frame_buff)[FRAMES][HEIGHT * WIDTH];
  int ch_dir_cd = 0;
  int stuck_cnt = 0;
  action_t action = ROTATE;
public:
  int life = 2;
  bool shot_st = false;

  Tank(int x, int y, int dir, int side);

  void move();
  void print();
  void back(bool stuck = false);
  void shot(std::list<Shell*> &shells);
  void update();
  void rotate(int new_dir);

  ~Tank();
};

