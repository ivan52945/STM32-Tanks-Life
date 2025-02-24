#pragma once

#include "tank.hpp"
#include "point.hpp"

bool is_booked(const point_t &point, const Tank &tank);

void spawn(std::list<Tank*> &tanks, int tanks_cnt[]);

void resolve_collizion(Tank &t_moved, Tank &t_stayed);

void resolve_collizion(Shell &shell, Tank &tank);
