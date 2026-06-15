#include "../include/board.h"
#include "../include/ui.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  initscr();

  // check for color support
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();
  use_default_colors();

  // initialize color pairs
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_YELLOW, -1);

  raw();                // no CTRL+C allowed, only q
  keypad(stdscr, TRUE); // i need the arrow keys
  noecho();             // disable annoying text buffering
  curs_set(0);
  refresh();

  int screen_rows, screen_cols;
  getmaxyx(stdscr, screen_rows, screen_cols);

  int height = 6 * 3;
  int width = 7 * 6;

  int starty = (screen_rows - height) / 2;
  int startx = (screen_cols - width) / 2;

  WINDOW *selection_win = newwin(3, width, starty, startx);
  WINDOW *board_win = newwin(height, width, starty + 3, startx);

  if (board_win == NULL) {
    endwin();
    printf("newwin failed\n");
    return 1;
  }

  // game variables
  state_t current_player =
      choose_player(); // will call the entire pre-game selection menu
  cell_t(*board)[7] = init_board();
  int selected_col = 0;
  bool game_over = false;
  bool draw_game = false;

  // Main program loop
  while (1) {
    draw(board_win, selection_win, board, starty, height, selected_col,
         current_player, game_over, draw_game);

    int ch = getch();

    if (ch == 'q') {
      break;
    }

    // check if game ended
    if (!game_over) {

      // handle other input
      switch (ch) {

      // handle resize
      case KEY_RESIZE:
        getmaxyx(stdscr, screen_rows, screen_cols);

        starty = (screen_rows - height) / 2;
        startx = (screen_cols - width) / 2;

        mvwin(selection_win, starty, startx);
        mvwin(board_win, starty + 3, startx);

        clear();
        refresh();
        break;

      case KEY_LEFT:
        if (selected_col > 0) {
          selected_col--;
        }
        break;

      case KEY_RIGHT:
        if (selected_col < 6) {
          selected_col++;
        }
        break;

      // space_key
      case ' ':
        int row =
            drop_chip(board, selected_col, current_player, board_win,
                      selection_win, starty, height, game_over, draw_game);

        if (row != -1) {

          if (check_winner(board, row, selected_col, current_player)) {
            game_over = true;
          } else if (board_full(board)) {
            draw_game = true;
            game_over = true;
          } else {
            // interpolate player based on previous color
            current_player = (current_player == RED) ? YELLOW : RED;
          }
        }
        break;
      }
    }
  }

  delwin(board_win);
  endwin();
  return 0;
}
