// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

#include "movement.h"

static float x_speed_compensation = 0.6;
static float speed = 0.25;
static float head_y, head_x;

void player_movement(int *game_state, int game_border_y, int game_border_x)
{
  head_y = get_snake_head_y();
  head_x = get_snake_head_x();
  // cases for constant movement of snake
  if (is_snake_forw())
  {
    set_snake_head(head_y - speed, head_x, head_y, head_x);
  }

  else if (is_snake_back())
  {
    set_snake_head(head_y + speed, head_x, head_y, head_x);
  }

  else if (is_snake_right())
  {
    set_snake_head(head_y, head_x + (speed + x_speed_compensation),
                   head_y, head_x);
  }

  else if (is_snake_left())
  {
    set_snake_head(head_y, head_x - (speed + x_speed_compensation),
                   head_y, head_x);
  }

  // gets player input and changes dirction
  char c = tolower(getch()); // reads char imput from player

  // if else if is used because we also need to check
  // * the current dirrection of the snake
  if (c == 'w' && !is_snake_back())
  {
    sound_play("sounds/change_dirr.wav");
    snake_forw();
  }

  else if (c == 's' && !is_snake_forw())
  {
    sound_play("sounds/change_dirr.wav");
    snake_back();
  }

  else if (c == 'a' && !is_snake_right())
  {
    sound_play("sounds/change_dirr.wav");
    snake_left();
  }

  else if (c == 'd' && !is_snake_left())
  {
    sound_play("sounds/change_dirr.wav");
    snake_right();
  }

  else if (c == ' ') // Enables Pause Scrren when Space is Pressed
  {
    sound_play("pause.wav");
    while (1)
    {
      draw_pause_screen(game_border_y, game_border_x);
      refresh();
      char ch = getch();
      if (ch == ' ')
      {
        break;
      }
    }
  }

  // Shows Quit screen wehen pressing esc (esc = 27 in ascii value)
  else if (c == 27)
  {
    sound_play("sounds/press.wav");
    draw_quit_screen(*game_state, game_border_y, game_border_x);
  }

  while (getch() != EOF) // empties char buffer
  {
  }
}
