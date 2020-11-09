// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>
#include "snake.h"
#include "draw.h"
#include "sound.h"

#pragma once

// moves the Snake and gets player Inputs while gameplay is running
void player_movement(int * game_state, int game_border_y, int game_border_x);