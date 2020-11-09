// (c) 2020 by Nico Mayer BME2 StudienArbeit CURSNAKE

#include "collision.h"

static int head_y, head_x;
static int mask = A_CHARTEXT | A_ALTCHARSET;
static bool collision_on = false; // decides if the walls are Open or Not

void check_wall_collision(int *game_state, int min_y, int min_x,
                          int max_y, int max_x)
{
  head_y = (int)get_snake_head_y();
  head_x = (int)get_snake_head_x();

  if (head_x - 3 > max_x) // collision with right game wall
  {
    if (collision_on)
    {
      *game_state = 3;
    }
    else
    {
      head_x = min_x + 1;
      set_snake_head(head_y, head_x, 0, 0);
    }
  }
  else if (head_x - 1 < min_x) // collision left left game wall
  {
    if (collision_on)
    {
      *game_state = 3;
    }
    else
    {
      head_x = max_x + 3;
      set_snake_head(head_y, head_x, 0, 0);
    }
  }
  else if (head_y + 1 > max_y) // collision with lower game wall
  {
    if (collision_on)
    {
      *game_state = 3;
    }
    else
    {
      head_y = min_y + 1;
      set_snake_head(head_y, head_x, 0, 0);
    }
  }
  else if (head_y - 1 < min_y) // collision with upper game wall
  {
    if (collision_on)
    {
      *game_state = 3;
    }
    else
    {
      head_y = max_y;
      set_snake_head(head_y, head_x, 0, 0);
    }
  }
}
void check_fruit_collision(int *score)
{
  head_y = get_snake_head_y();
  head_x = get_snake_head_x();

  int ch = mvinch(head_y, head_x) & mask;
  if (ch == fruit_symbol()) // checks if head is over a Fruit
  {
    sound_play("sounds/pickup.wav");
    fruit_set_false();
    increase_snake_length();
    *score += 5;
  }
}
void check_body_collision(int *game_state)
{
  head_y = get_snake_head_y();
  head_x = get_snake_head_x();

  if (is_snake_forw()) // checkes collision when snake is moving forward
  {
    int ch = mvinch(head_y - 1, head_x) & mask;
    if (ch == get_body_symbol())
    {
      *game_state = 3;
    }
  }
  else if (is_snake_back()) // checkes collision when snake is moving backwards
  {
    int ch = mvinch(head_y + 1, head_x) & mask;
    if (ch == get_body_symbol())
    {
      *game_state = 3;
    }
  }
  else if (is_snake_right()) // checkes collision when snake is moving right
  {
    int ch = mvinch(head_y, head_x + 1) & mask;
    if (ch == get_body_symbol())
    {
      *game_state = 3;
    }
  }
  else if (is_snake_left()) // checkes collision when snake is moving left
  {
    int ch = mvinch(head_y, head_x - 1) & mask;
    if (ch == get_body_symbol())
    {
      *game_state = 3;
    }
  }
}
void change_wall_collision_mode(int on_off)
{
  if (on_off == 0)
  {
    collision_on = false;
  }
  else if (on_off == 1)
  {
    collision_on = true;
  }
}
