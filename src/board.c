#include "../include/board.h"
#include <ncurses.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define CELL_H 3
#define CELL_W 6

void draw_board(WINDOW *win, cell_t board[6][7]) {
  // initialize color pairs
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);

  // draw
  box(win, 0, 0);

  for (int r = 0; r < 6; ++r) {
    for (int c = 0; c < 7; ++c) {

      int y = 1 + r * CELL_H;
      int x = 2 + c * CELL_W;

      char symbol = '0';

      if (board[r][c].state == RED) {
        symbol = 'R';
        attrset(COLOR_PAIR(1));
      } else if (board[r][c].state == YELLOW) {
        attrset(COLOR_PAIR(2));
        symbol = 'Y';
      }

      mvwaddch(win, y, x, symbol);
      standend();
    }
  }
}

cell_t (*init_board(void)) [COLS] {
  cell_t(*board)[COLS] = malloc(ROWS * sizeof(*board));
  if (board == NULL)
    return NULL;

  for (int r = 0; r < ROWS; ++r) {
    for (int c = 0; c < COLS; ++c) {
      board[r][c].row_num = r + 1;
      board[r][c].col_num = c + 1;
      board[r][c].state = EMPTY;
    }
  }

  return board;
}

void check_occupied(cell_t board[6][7], int selected_col) {
  int num_free = 6;
  for (int i = 0; i < 6; ++i) {
    if (board[i][selected_col].state != EMPTY) {
      num_free--;
    }
  }
}

void drop_chip(WINDOW *win, cell_t board[6][7], int selected_col) {
  switch (selected_col) {
  case 1:
    // do stuff
  }
}
