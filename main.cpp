// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>

#include "sound.h"
#include "draw.h"
#include "movement.h"
#include "collision.h"
#include "fruit.h"
#include "gridfont.h"

// instance variables
static int score = 0;                    // score of the player;
static int game_state = 4;               // current game state var
static int max_x = 0, max_y = 0;         // x and y Maximal of current terminal window
static int game_border_x, game_border_y; // max of y and x of the game border
// offset from screen border to game border y achse
static int game_border_y_offset = 2;
// offset from screen border to game border x achse
static int game_border_x_offset = 4;
static float time = 0; //time counter since start of the game

// forward declaration using function prototype
void init();
void init_colorsets();
void game_loop();
void add_fruits();
void gameplay(int us, float dt);

int main()
{
  init();       // inits all nesaserry funktions for snake
  game_loop();  // game loop with gamplay and menus
  sound_exit(); // exits sdl sound
  endwin();     // exits program and restors default settings

  return (0);
}

void game_loop()
{
  // Constants
  static const int fps = 40;              // fps of the game
  static const float dt = 1.0 / fps;      // Delta Time
  static const int us = 1000 * 1000 * dt; // dt in micro sec
  while (1)
  {
    if (game_state == 4) // Start Menu is Displyed here
    {
      while (game_state == 4)
      {
        draw_start_screen(&game_state, us);
      }
    }

    if (game_state == 1) // Settings Menu is Displyed here
    {
      while (game_state == 1)
      {
        draw_settings_menu(&game_state, us);
      }
    }

    if (game_state == 0) // Game is Played here
    {
      // inits the snake to game canvas for the first time
      init_snake(game_border_y / 2,
                 (game_border_x / 2) + game_border_x_offset);
      while (game_state == 0)
      {
        gameplay(us, dt);
      }
    }

    if (game_state == 3) // Loose State
    {
      sound_play("sounds/hurt.wav");

      // Hiscore Test
      FILE *file_ptr;

      file_ptr = fopen("hiscore.txt", "wb");
      fprintf(file_ptr, "%d", score);
      fclose(file_ptr);

      // Resets the Game Values
      time = 0;
      score = 0;

      while (game_state == 3)
      {
        draw_loose_screen(game_border_y, game_border_x);
        refresh();
        char ch = getch();
        if (ch == 10)
        {
          game_state = 4;
          break;
        }
      }
    }

    if (game_state == 2) // closing the hole program
    {
      break;
    }
  }
}

void gameplay(int us, float dt)
{
  clear();
  // gets the max_y and max_x from terminal window even wehen the size changes
  getmaxyx(stdscr, max_y, max_x);
  // dynamicly changes game border height in dependence of Terminal rows
  game_border_y = max_y * 0.9;
  // dynamicly changes game border width in dependence of Terminal cols
  game_border_x = max_x * 0.7;

  // draw & movement
  draw_border(3); // draws Green border to game screen
  draw_box(game_border_y_offset, game_border_x_offset,
           game_border_y, game_border_x);
  // scoreboard that displays points time and contols
  draw_score_board(score, time);
  // function to print player and detect player movement with W A S D
  player_movement(&game_state, game_border_y, game_border_x);
  // adds a Fruit within the game border
  add_fruits(game_border_y_offset, game_border_x_offset,
             game_border_y, game_border_x);

  // collision checks
  check_wall_collision(&game_state, game_border_y_offset,
                       game_border_x_offset, game_border_y, game_border_x);
  check_fruit_collision(&score);
  check_body_collision(&game_state);

  refresh();
  usleep(us); // sleeps for the time us
  time += dt; // adds delta time to total time with every pass
}

void init()
{
  initscr();  // init terminal window
  timeout(0); //stops getch() from blocking the animations
  getmaxyx(stdscr, max_y, max_x);
  game_border_y = max_y * 0.9;
  game_border_x = max_x * 0.7;
  sound_init();     // init sdl sound();
  curs_set(false);  // set curser off
  noecho();         // hide keyboard input
  init_grid_font(); //inits gridfont text 5x3
  init_colorsets(); // init the needed color sets
  sound_play("sounds/start.wav");
  clear();   // clears Screen
  refresh(); // refresehes screen, and changes getting visible
}

void init_colorsets()
{
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);   // White font Black Background
  init_pair(2, COLOR_RED, COLOR_BLACK);     // Red font Black Background
  init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Green font Black Background
  init_pair(4, COLOR_BLUE, COLOR_BLACK);    // Blue font Black Background
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Yellow font on Black Background
  init_pair(6, COLOR_CYAN, COLOR_BLACK);    // Cyan font on Black Background
  init_pair(7, COLOR_MAGENTA, COLOR_BLACK); // Magenta font on Black Background
}
