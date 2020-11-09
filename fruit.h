// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>
#include "graphics.h"
#include "sound.h"

#pragma once

//adds fruit to game within the game border
void add_fruits(int min_y, int min_x, int game_border_y, int game_border_x);

// gets y coor from fruit (not used atm, but maybe usefull in future updates)
int fruit_get_y();

// gets x coor from fruit (not used atm, but maybe usefull in future updates)
int fruit_get_x();

// returns the current fruit symbol as a char
char fruit_symbol();

// sets a bool to false so that a nother fruit can be spawnt
void fruit_set_false();