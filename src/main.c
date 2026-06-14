#include "../include/board.h"
#include "../include/ui.h"
#include <inttypes.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void draw(WINDOW *board_win, WINDOW *selection_win, cell_t board[6][7],
          int starty, int board_height, int selected_col) {
  werase(selection_win);
  werase(board_win);
  draw_selection(selection_win, selected_col);
  draw_board(board_win, board);
  draw_controls(starty, board_height);
  wrefresh(selection_win);
  wrefresh(board_win);
}

state_t choose_player(void) {
  int selected = 0;

  int height = 5;
  int width = 30;

  int y = (LINES - height) / 2;
  int x = (COLS - width) / 2;

  WINDOW *win = newwin(height, width, y, x);

  while (1) {
    werase(win);
    box(win, 0, 0);

    // arrows
    if (selected == 0) {
      mvwprintw(win, 1, 6, "v");
    } else {
      mvwprintw(win, 1, 20, "v");
    }

    // Red Player
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 2, 2, "Red Player");
    wattroff(win, COLOR_PAIR(1));

    // Yellow Player
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 2, 15, "Yellow Player");
    wattroff(win, COLOR_PAIR(2));

    wrefresh(win);

    int ch = getch();

    switch (ch) {
    case KEY_LEFT:
      selected = 0;
      break;

    case KEY_RIGHT:
      selected = 1;
      break;

    case ' ':
    case '\n':
      delwin(win);
      return selected == 0 ? RED : YELLOW;
    }
  }
}

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

  raw();
  keypad(stdscr, TRUE);
  noecho();
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
  state_t player_color =
      choose_player(); // will call the entire pre-game selection menu
  cell_t(*board)[7] = init_board();
  int selected_col = 0;

  // Main program loop
  while (1) {
    draw(board_win, selection_win, board, starty, height, selected_col);

    int ch = getch();

    if (ch == 'q')
      break;

    // handle other input
    switch (ch) {
    case KEY_LEFT:
      if (selected_col > 0)
        selected_col--;
      break;

    case KEY_RIGHT:
      if (selected_col < 6)
        selected_col++;
      break;

    case ' ':
      drop_chip(board, selected_col, player_color);
      break;
    }
  }

  delwin(board_win);
  endwin();
  return 0;
}
