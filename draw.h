// (c) 2020 by Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>
#include <string.h>
#include "graphics.h"
#include "sound.h"
#include "gridfont.h"
#include "snake.h"
#include "collision.h"

//test
#include "sprites.h"

#pragma once

// Draws a Boder and takes a int for the selected color pair
void draw_border(int color_index);

// Draws a box with horizontal char '_' and vertical char '|'
void draw_box(int dy, int dx, int height, int length);

// Draws the game Infos to the Game Screen points time and controls 
void draw_score_board(int points, int time);

// Draws the Start Screen Ascii Graphic Header and Main Menu
// * takes Pointer to game State, can start game, go to settings 
// * and close entire window
void draw_start_screen(int * game_state, float us);

// Draws the Current Terminal Window to y x
void draw_screen_size(int y, int x);

// Draws the Pause Screen (Needs some Improvment to Dynamicly
// * reszie when Window is pulled bigger or Smaller)
void draw_pause_screen(int game_border_y, int game_border_x);

// Draws the Loose Screen (Needs some Improvment to Dynamicly
// * reszie when Window is pulled bigger or Smaller)
void draw_loose_screen(int game_border_y, int game_border_x);

// Draws the hole Settings menue (Needs some Improfments to mutch
// * code in ths funktion, try to shape it down and make it more practical)
void draw_settings_menu(int * game_state, float us);

// Draws the Quit Screen (Needs some Improvment to Dynamicly
// * reszie when Window is pulled bigger or Smaller)
void draw_quit_screen(int & game_state, int game_border_y, int game_border_x);
