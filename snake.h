// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

//Needed Includes
#include <ncurses.h>
#include "graphics.h"

#pragma once

// Struct for Body Parts of the snake with
struct Body
{
  int prev_y, prev_x;
  int next_y, next_x;
};

// char array of all possible Snake body Skins
static const char body_symbols[] = "o0#SUV&X";

// returns char of the snake body
char get_body_symbol();

// changes the snake colot, takes a char bsp: b = blue
void set_snake_color(int color);

// changes the body char to the char in body_symbols on i
void set_snake_body_char(int i);

// increases the snake length by 2 (2 because it feels better for the gameplay)
void increase_snake_length();

// draws the head of the snake to pos (y,x)
//* (needs some impfovment for body movment function to big)
void set_snake_head(float head_y, float head_x, float prev_y, float prev_x);

// inits the snake head and start body on pos (y,x) 
void init_snake(int y, int x);

// returns the current pos of the heads y pos
float get_snake_head_y();
// returns the current pos of the snaks x pos
float get_snake_head_x();

// sets the dirrection of the snake to forward
void snake_forw();
// sets the dirrection of the snake to backwards
void snake_back();
// sets the dirrection of the snake to left
void snake_left();
// sets the dirrection of the snake to right
void snake_right();

// these funktions are checking the
// * current dirrection of the snake (true or false)
bool is_snake_forw();
bool is_snake_back();
bool is_snake_left();
bool is_snake_right();
