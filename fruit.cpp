// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

#include "fruit.h"

static bool fruit_on = false;
static int fruit_y, fruit_x;
static const char fruit = '$';

void add_fruits(int min_y, int min_x, int game_border_y, int game_border_x)
{
  if (!fruit_on)
  {
    fruit_y = (game_border_y - 1) * rnd();
    fruit_x = (game_border_x - 1) * rnd();
    if (fruit_y <= min_y)
    {
      fruit_y = min_y + 2;
    }
    
    if (fruit_x <= min_x)
    {
      fruit_x = min_x + 2;
    }
    
    color_set(2, NULL);
    mvaddch(fruit_y, fruit_x, fruit);
    color_set(1, NULL);
    fruit_on = true;
  }
  color_set(2, NULL);
  mvaddch(fruit_y, fruit_x, fruit);
  color_set(1, NULL);
}

int fruit_get_y()
{
  return (fruit_y);
}

int fruit_get_x()
{
  return (fruit_x);
}

char fruit_symbol()
{
  return (fruit);
}

void fruit_set_false()
{
  fruit_on = false;
}
