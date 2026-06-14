#include "../include/board.h"
#include "../include/ui.h"
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

int main(void) {
  initscr();

  // check for color support
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();
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
      // detect lowest empty cell
      break;
    }
  }

  delwin(board_win);
  endwin();
  return 0;
}
