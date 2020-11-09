// (c) 2020 by Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>
#include "snake.h"
#include "sound.h"
#include "fruit.h"

#pragma once

// Detects snake collision with walls of the level enter limits as arguments
// * can change the game state if snake hits the wall
void check_wall_collision(int * game_state, int min_y, int min_x,
                          int max_y, int max_x);

// Detects snake collision with fruit, takes a Pointer to score value
// * and increases it by 5 when the snake hits a Fruit
void check_fruit_collision(int * score);

// Checks if snake collide with her own body, takes Pointer to game_state and
// * ends the game when snake hits it self
void check_body_collision(int * game_state);

// Funktion to change the wall collision Mode 
// * takes a int value
// * if on_off = 0 => Walls are open
// * if on_off = 1 => Walls are closed 
void change_wall_collision_mode(int on_off);
