#include "list"
#include "math.h"
#include "shell.hpp"
#include "point.hpp"
#include "game.hpp"
#include "tank.hpp"

bool is_booked(const point_t &point, const Tank &tank)
{
  const int dist_x = TANK_WIDTH - 1 + 2;
  const int dist_y = TANK_WIDTH - 1 + 2;
  
  if ((fabs(point.x - tank.x) >= dist_x) || (fabs(point.y - tank.y) >= dist_y))
    return false;
  
  return true;
}

void spawn(std::list<Tank*> &tanks, int tanks_cnt[])
{
  for (int i = 0; i < 2; ++i) {
    for (int s_i = 0; (s_i < 7) && (tanks_cnt[i] > 0); ++s_i) {
      bool is_free = true;
      
      for (auto tank : tanks) {
        if (!is_booked(tank_spawns[i][s_i], *tank))
          continue;
        
        is_free = false;
        break;
      }
      
      if (!is_free)
        continue;
      
      tanks.push_back(new Tank(tank_spawns[i][s_i].x, tank_spawns[i][s_i].y, 1 + i * 2, i));
      tanks_cnt[i] -= 1;
    }
  }
}

void resolve_collizion(Tank &t_moved, Tank &t_stayed)
{
  const int dist_x = TANK_WIDTH - 1;
  const int dist_y = TANK_WIDTH - 1;
  
  if ((fabs(t_moved.x - t_stayed.x) >= dist_x) || (fabs(t_moved.y - t_stayed.y) >= dist_y))
    return;
  
  t_moved.back(true);
}

void resolve_collizion(Shell &shell, Tank &tank)
{
  const int dist_x = TANK_WIDTH / 2 + SHELL_LENGTH / 2;
  const int dist_y = TANK_WIDTH / 2 + SHELL_LENGTH / 2;
  
  if ((fabs(tank.x - shell.x) >= dist_x) || (fabs(tank.y - shell.y) >= dist_y))
    return;
  
  shell.life = false;
  
  if (shell.side == tank.side)
    return;
  
  if (abs(shell.dir - tank.dir) == 2)
    tank.life -= 1;
  else
    tank.life -= 2;
}
