// (c) Nico Mayer BME2 StudienArbeit CURSNAKE

#include "draw.h"

static int header_x, header_y;
static int max_x = 0, max_y = 0;

// Protototypes
void draw_screen_size(int x, int y);
void draw_infos();
void draw_control_info();
void animate_snake_header(float us);
void animate_settings_header(float us);

void draw_border(int color_index)
{
  //  colored frame
  color_set(color_index, NULL);
  border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
         ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  color_set(1, NULL);
}

void draw_box(int dy, int dx, int height, int length)
{
  // gets the max_y and max_x from terminal window even wehen the size changes
  getmaxyx(stdscr, max_y, max_x);
  // dynamic funktion to get the correct x pos for the Scoreboard Header
  header_x = max_x - ((max_x - (dx + length)) / 2);
  header_y = dy + 1;
  attrset(A_BOLD);
  draw_line(dy, dx, dy, dx + length, '_'); // upper Horizontal line
  draw_line(height, dx, dy, dx, '|');      // left Vertical line
  // right Vertical line
  draw_line(dy, dx + length, height, dx + length, '|');
  // lower Horizontal line
  draw_line(height, dx + length, height, dx, '_');
  attrset(A_NORMAL);
}

void draw_score_board(int points, int time)
{
  draw_screen_size(1, 2);
  draw_infos();
  // draws Header of scoreboard
  attrset(A_BOLD);
  color_set(3, NULL);
  mvprintw(header_y, header_x - 4, "SNAKE");
  color_set(1, NULL);
  // draws score indicator
  mvprintw(header_y + 2, header_x - 4, "Points: %i", points);
  // draws time indicator
  mvprintw(header_y + 3, header_x - 4, "Time: %i", time);
  attrset(A_NORMAL);
  draw_control_info();
}

void draw_control_info()
{
  attrset(A_BOLD);
  color_set(3, NULL);
  mvprintw(header_y + 5, header_x - 4, "Controls");

  color_set(1, NULL);
  attrset(A_NORMAL);
  mvprintw(header_y + 7, header_x - 4, "UP    = 'W'");
  mvprintw(header_y + 8, header_x - 4, "Down  = 'S'");
  mvprintw(header_y + 9, header_x - 4, "RIGHT = 'D'");
  mvprintw(header_y + 10, header_x - 4, "LEFT  = 'A'");
  mvprintw(header_y + 11, header_x - 4, "Pause = SPACE");
  color_set(2, NULL);
  mvprintw(header_y + 13, header_x - 4, "Quit  = ESC");
  color_set(1, NULL);
}

void draw_start_screen(int *game_state, float us)
{
  //Following Menue Part is inspired by Q2
  int choice;
  int highlight = 0;
  char choices[3][50];

  strcpy(choices[0], "1.) PLAY!");
  strcpy(choices[1], "2.) SETTINGS");
  strcpy(choices[2], "3.) QUIT");

  clear();
  while (1)
  {
    // gets the max_y and max_x from terminal window
    // * even wehen the size changes
    getmaxyx(stdscr, max_y, max_x);
    draw_border(3);
    draw_screen_size(1, 2);
    draw_infos();

    // draws Header Sprite for start screem
    animate_snake_header(us);
    mvprintw(max_y * 0.36, max_x * 0.65, "by Nico Mayer");

    // draws box for menue Items
    draw_box(max_y * 0.4, max_x * 0.25, max_y * 0.85, max_x * 0.5);

    // print the menue items
    for (int i = 0; i < 3; i++)
    {
      if (i == highlight)
      {
        attron(A_REVERSE | A_BOLD);
        color_set(3, NULL);
        mvprintw(max_y * 0.55 + i, max_x * 0.45, choices[i]);
        color_set(1, NULL);
        attroff(A_REVERSE);
      }

      else
      {
        mvprintw(max_y * 0.55 + i, max_x * 0.45, choices[i]);
      }
    }

    // switch chase over the menue Items
    choice = tolower(getch());
    switch (choice)
    {
    case 'w':
      if (highlight > 0) // checks if the highlighter gets out of bounds
      {
        sound_play("sounds/press.wav");
        highlight--;
      }
      break;
    case 's':

      if (highlight < 2) // checks if the highlighter gets out of bounds
      {
        sound_play("sounds/press.wav");
        highlight++;
      }
      break;
    default:
      break;
    }
    // when hit enter we break out the while loop
    if (choice == 10)
    {
      if (highlight == 2)
      {
        sound_play("sounds/exit.wav");
      }
      else
      {
        sound_play("sounds/select.wav");
      }
      usleep(500000); // sleep for 0,5s to play the sound
      clear();
      *game_state = highlight;
      break;
    }
    refresh();
    usleep(us);
  }
}

void animate_snake_header(float us)
{
  attrset(A_BOLD);
  color_set(3, NULL);
  static float delta_time = 0;
  static const float animation_length = 0.25;
  static const float dt = 1.0 / 40;
  if (delta_time < animation_length)
  {
    draw_sprite(max_y * 0.23, max_x * 0.47, snake_header_1);
    delta_time += dt;
  }
  if (delta_time > animation_length)
  {
    draw_sprite(max_y * 0.23, max_x * 0.47, snake_header_2);
    delta_time += dt;
  }
  if (delta_time > 2 * animation_length)
  {
    draw_sprite(max_y * 0.23, max_x * 0.47, snake_header_3);
    delta_time += dt;
  }
  if (delta_time > 3 * animation_length)
  {
    draw_sprite(max_y * 0.23, max_x * 0.47, snake_header_4);
    delta_time += dt;
    if (delta_time > 4 * animation_length)
    {
      delta_time = 0;
    }
  }
  color_set(1, NULL);
  attrset(A_NORMAL);
}

void draw_settings_menu(int *game_state, float us)
{
  static const int menu_options = 4;
  static const int color_options = 7;
  static const int on_off_options = 2;
  static const int body_skin_options = 8;

  static int choice;            // for detecting user input
  static int select_color = 2;  // start with green color
  static int on_off_select = 0; // starts with on
  static int highlight = 0;
  static int len;

  static int body_skin_selected = 0;

  // String Array for Main Settings Options
  char choices[menu_options][50];
  strcpy(choices[0], "1.) SELECT SNAKE COLOR:");
  strcpy(choices[1], "2.) Open Walls:");
  strcpy(choices[2], "3.) Select Body Skin:");
  strcpy(choices[3], "4.) BACK");

  // String Array for Color Options
  char colors[color_options][15];
  strcpy(colors[0], "< white   >");
  strcpy(colors[1], "< red     >");
  strcpy(colors[2], "< green   >");
  strcpy(colors[3], "< blue    >");
  strcpy(colors[4], "< yellow  >");
  strcpy(colors[5], "< cyan    >");
  strcpy(colors[6], "< magenta >");

  // String Array for Open Walls Switch
  char on_off[2][10];
  strcpy(on_off[0], "< on  >");
  strcpy(on_off[1], "< off >");

  // String Array for Body Skin Options
  char body_skins[body_skin_options][10];
  strcpy(body_skins[0], "< o >");
  strcpy(body_skins[1], "< 0 >");
  strcpy(body_skins[2], "< # >");
  strcpy(body_skins[3], "< S >");
  strcpy(body_skins[4], "< U >");
  strcpy(body_skins[5], "< V >");
  strcpy(body_skins[6], "< & >");
  strcpy(body_skins[7], "< X >");

  len = strlen(choices[0]);
  getmaxyx(stdscr, max_y, max_x);

  clear();
  while (1)
  {
    getmaxyx(stdscr, max_y, max_x);
    draw_screen_size(1, 2);
    draw_infos();
    draw_border(5);

    // Draws Header for Settings Menu
    animate_settings_header(us);

    // draws box (y_off,x_off,height,length) for menue Items
    draw_box(max_y * 0.4, max_x * 0.25, max_y * 0.85, max_x * 0.5);

    // print the menue items
    for (int i = 0; i < menu_options; i++)
    {
      if (i == highlight)
      {
        attron(A_REVERSE | A_BOLD);
        color_set(5, NULL);
        mvprintw(max_y * 0.55 + i, (max_x / 2) - len, choices[i]);
        color_set(1, NULL);
        attroff(A_REVERSE);
      }
      else
      {
        mvprintw(max_y * 0.55 + i, (max_x / 2) - len, choices[i]);
      }
    }

    // print the color picker
    for (int i = 0; i < color_options; i++)
    {
      // the option to select snake color is highlighted
      if (select_color == i && highlight == 0)
      {
        attron(A_REVERSE);
        color_set(i + 1, NULL);
        mvprintw(max_y * 0.55, (max_x / 2) + 10, colors[i]);
        color_set(1, NULL);
        attroff(A_REVERSE);
      }
      // option to change snake color not selected
      else if (select_color == i && highlight != 0)
      {
        mvprintw(max_y * 0.55, (max_x / 2) + 10, colors[i]);
      }
    }

    // print on_off switch
    for (int i = 0; i < on_off_options; i++)
    {
      // the option for Open Walls is highlighted
      if (highlight == 1 && on_off_select == i)
      {
        attron(A_REVERSE);
        mvprintw(max_y * 0.55 + 1, (max_x / 2) + 10, on_off[i]);
        attroff(A_REVERSE);
      }
      // option for Open walls not selected
      else if (highlight != 1 && on_off_select == i)
      {
        mvprintw(max_y * 0.55 + 1, (max_x / 2) + 10, on_off[i]);
      }
    }

    // print body skin picker
    for (int i = 0; i < body_skin_options; i++)
    {
      if (body_skin_selected == i && highlight == 2)
      {
        attron(A_REVERSE);
        mvprintw(max_y * 0.55 + 2, (max_x / 2) + 10, body_skins[i]);
        attroff(A_REVERSE);
      }
      else if (body_skin_selected == i && highlight != 2)
      {
        mvprintw(max_y * 0.55 + 2, (max_x / 2) + 10, body_skins[i]);
      }
    }

    // switch case over the menue Items General Controlls
    choice = tolower(getch());
    switch (choice)
    {
    case 'w':
      // checks if the highlighter gets out of bounds
      if (highlight > 0)
      {
        sound_play("sounds/press.wav");
        highlight--;
      }
      break;
    case 's':
      // checks if the highlighter gets out of bounds
      if (highlight < menu_options - 1)
      {
        sound_play("sounds/press.wav");
        highlight++;
      }
      break;
    case 'd':
      // color selection option is
      // * highlighted and selection not out of range
      if (highlight == 0 && select_color < color_options - 1)
      {
        sound_play("sounds/press.wav");
        select_color++;
      }
      // Open Walls selection is highlighted
      else if (highlight == 1 && on_off_select < on_off_options - 1)
      {
        sound_play("sounds/press.wav");
        on_off_select++;
      }
      // Body Picker Highlited
      else if (highlight == 2 &&
               body_skin_selected < body_skin_options - 1)
      {
        sound_play("sounds/press.wav");
        body_skin_selected++;
      }
      break;
    case 'a':
      // color selection option is highlighted
      // * and selection not out of range
      if (highlight == 0 && select_color > 0)
      {
        sound_play("sounds/press.wav");
        select_color--;
      }
      // Open Walls selection is highlighted
      else if (highlight == 1 && on_off_select > 0)
      {
        sound_play("sounds/press.wav");
        on_off_select--;
      }
      // Body Picker Highlited
      else if (highlight == 2 && body_skin_selected > 0)
      {
        sound_play("sounds/press.wav");
        body_skin_selected--;
      }
      break;
    default:
      break;
    }
    // when hit enter we break out the while loop
    if (choice == 10)
    {
      usleep(500000); // sleep for 0,5s to play the sound
      clear();
      // when back is selected we go back to the Main Menu
      if (highlight == menu_options - 1)
      {
        sound_play("sounds/select.wav");
        *game_state = 4;
      }

      // Changes Color of the snake to select color
      else if (highlight == 0)
      {
        sound_play("sounds/save.wav");
        set_snake_color(select_color);
      }
      // Changes Snake body Skin
      else if (highlight == 2)
      {
        sound_play("sounds/save.wav");
        set_snake_body_char(body_skin_selected);
      }

      // Sets Open Walls True
      else if (on_off_select == 0 && highlight == 1)
      {
        sound_play("sounds/save.wav");
        change_wall_collision_mode(on_off_select);
      }
      // Sets Open Walls False
      else if (on_off_select == 1 && highlight == 1)
      {
        sound_play("sounds/save.wav");
        change_wall_collision_mode(on_off_select);
      }
      break;
    }
    refresh();
    usleep(us);
  }
}

void animate_settings_header(float us)
{
  attrset(A_BOLD);
  color_set(5, NULL);
  static float delta_time = 0;
  static const float animation_length = 0.25;
  static const float dt = 1.0 / 40;
  if (delta_time < animation_length)
  {
    draw_sprite(max_y * 0.25, max_x * 0.47, settings_header_1);
    delta_time += dt;
  }
  if (delta_time > animation_length)
  {
    draw_sprite(max_y * 0.25, max_x * 0.47, settings_header_2);
    delta_time += dt;
  }
  if (delta_time > 2 * animation_length)
  {
    draw_sprite(max_y * 0.25, max_x * 0.47, settings_header_3);
    delta_time += dt;
  }
  if (delta_time > 3 * animation_length)
  {
    draw_sprite(max_y * 0.25, max_x * 0.47, settings_header_4);
    delta_time += dt;
    if (delta_time > 4 * animation_length)
    {
      delta_time = 0;
    }
  }
  color_set(1, NULL);
  attrset(A_NORMAL);
}

void draw_quit_screen(int &game_state, int game_border_y, int game_border_x)
{
  while (1)
  {
    int choice;
    static int x_offset = 0;
    static int highlight = 1;
    attrset(A_BOLD);
    color_set(2, NULL);
    draw_grid_text(game_border_y * 0.15,
                   (game_border_x / 2) - 27, "Want to Quit?");

    color_set(1, NULL);
    attrset(A_NORMAL);

    char choices[2][10];

    strcpy(choices[0], "  YES  ");
    strcpy(choices[1], "  NO  ");

    for (int i = 0; i < 2; i++)
    {
      if (i == highlight)
      {
        if (i == 0)
        {
          x_offset = 0;
        }
        else
        {
          x_offset = 15;
        }
        attron(A_REVERSE);
        mvprintw((game_border_y * 0.15) + 4,
                 (game_border_x / 2) - 6 + x_offset, choices[i]);
        attroff(A_REVERSE);
      }
      else
      {
        if (i == 1)
        {
          x_offset = 15;
        }
        else
        {
          x_offset = 0;
        }
        mvprintw((game_border_y * 0.15) + 4,
                 (game_border_x / 2) - 6 + x_offset, choices[i]);
      }
    }
    choice = tolower(getch());
    switch (choice)
    {
    case 'a':
      if (highlight > 0)
      {
        sound_play("sounds/press.wav");
        highlight--;
        break;
      }
    case 'd':
      if (highlight < 1)
      {
        sound_play("sounds/press.wav");
        highlight++;
        break;
      }
    default:
      break;
    }
    // Enter was Pressed
    if (choice == 10)
    {
      sound_play("sounds/select.wav");
      if (highlight == 0)
      {
        highlight = 1;
        game_state = 4; // Go to Main Menu
        break;
      }
      if (highlight == 1) // No is selected dout Quit the game
      {
        highlight = 1;
        break;
      }
    }

    refresh();
  }
}

void draw_pause_screen(int game_border_y, int game_border_x)
{
  attrset(A_BOLD | A_BLINK);
  color_set(2, NULL);
  draw_grid_text((game_border_y * 0.15), (game_border_x / 2) - 7, "Pause");
  color_set(1, NULL);
  attrset(A_NORMAL);
}

void draw_loose_screen(int game_border_y, int game_border_x)
{
  attrset(A_BOLD);
  color_set(2, NULL);
  draw_grid_text((game_border_y * 0.15),
                 (game_border_x / 2) - 15, "YOU DIED");
  color_set(1, NULL);
  attrset(A_NORMAL);
  mvprintw((game_border_y * 0.15) + 4,
           (game_border_x / 2) - 8, "Press Enter to go to Menu");
}

void draw_screen_size(int y, int x)
{
  mvprintw(y, x, "Screen Size is %dx%d", COLS, LINES);
}

void draw_infos()
{
  char curr_control[] = "Current Controll: W A S D";
  int len = strlen(curr_control);
  mvprintw(1, max_x - (len + 2), curr_control);
}
