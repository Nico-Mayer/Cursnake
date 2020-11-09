// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

#include "snake.h"

static const char head_forw = '^';
static const char head_back = 'v';
static const char head_right = '>';
static const char head_left = '<';

static char body_symbol = body_symbols[0];

static int snake_color = 3;

static float curr_y_pos = 0;
static float curr_x_pos = 0;

static bool forward = true;
static bool backwards = false;
static bool left = false;
static bool right = false;

// forward declaration using function prototype
bool is_snake_forw();
bool is_snake_back();
bool is_snake_left();
bool is_snake_right();

static int snake_start_length = 10;
static int snake_length;
// try to make the length of the struct
// * array dynamic when you got enoutght time lest
static const int max_snake_length = 400;
static Body body[max_snake_length];

void set_snake_head(float head_y, float head_x, float prev_y, float prev_x)
{
  curr_y_pos = head_y;
  curr_x_pos = head_x;
  color_set(snake_color, NULL);
  // Algorythem for moving the snake body, every body
  // * part is following the previous in the body array
  for (int i = 0; i < snake_length; i++)
  {
    if (i == 0)
    {
      body[i].next_y = prev_y;
      body[i].next_x = prev_x;
      mvaddch(body[i].next_y, body[i].next_x, body_symbol);
    }
    else
    {
      body[i].next_y = body[i - 1].prev_y;
      body[i].next_x = body[i - 1].prev_x;
      mvaddch(body[i].next_y, body[i].next_x, body_symbol);
    }
  }
  for (int i = 0; i < snake_length; i++)
  {
    body[i].prev_y = body[i].next_y;
    body[i].prev_x = body[i].next_x;
  }
  // Setting snake head to its new Position
  attrset(A_BOLD);
  color_set(snake_color, NULL);
  if (is_snake_forw())
  {
    mvaddch(curr_y_pos, curr_x_pos, head_forw);
  }
  else if (is_snake_back())
  {
    mvaddch(curr_y_pos, curr_x_pos, head_back);
  }
  else if (is_snake_left())
  {
    mvaddch(curr_y_pos, curr_x_pos, head_left);
  }
  else if (is_snake_right())
  {
    mvaddch(curr_y_pos, curr_x_pos, head_right);
  }
  color_set(1, NULL);
  attrset(A_NORMAL);
}

void set_snake_color(int color)
{
  snake_color = (color + 1);
}

void set_snake_body_char(int i)
{
  body_symbol = body_symbols[i];
}

void init_snake(int y, int x)
{
  snake_forw();
  snake_length = snake_start_length;
  set_snake_head(y, x, 0, 0);
  for (int i = 0; i <= snake_length; i++)
  {
    body[i].prev_y = y + 1 + i;
    body[i].prev_x = x;
    mvaddch(body[i].prev_y, body[i].prev_x, 'o');
  }
}

void increase_snake_length()
{
  snake_length += 2;
}

char get_body_symbol()
{
  return (body_symbol);
}

float get_snake_head_y()
{
  return (curr_y_pos);
}
float get_snake_head_x()
{
  return (curr_x_pos);
}

bool is_snake_forw()
{
  if (forward)
  {
    return true;
  } 
  else
  {
    return false;
  }    
}

bool is_snake_back()
{
  if (backwards)
  {
    return true;
  } 
  else
  {
    return false;
  }    
}

bool is_snake_left()
{
  if (left)
  {
    return true;
  } 
  else
  {
    return false;
  }    
}

bool is_snake_right()
{
  if (right)
  {
    return true;
  } 
  else
  {
    return false;
  }    
}

void snake_forw()
{
  forward = true;
  backwards = false;
  left = false;
  right = false;
}

void snake_back()
{
  forward = false;
  backwards = true;
  left = false;
  right = false;
}

void snake_left()
{
  forward = false;
  backwards = false;
  left = true;
  right = false;
}

void snake_right()
{
  forward = false;
  backwards = false;
  left = false;
  right = true;
}
