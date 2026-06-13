#include "../include/board.h"
#include <ncurses.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define CELL_H 3
#define CELL_W 6

void draw_board(WINDOW *win, cell_t board[6][7]) {
  box(win, 0, 0);

  for (int r = 0; r < 6; ++r) {
    for (int c = 0; c < 7; ++c) {

      int y = 1 + r * CELL_H;
      int x = 2 + c * CELL_W;

      char symbol = '0';

      if (board[r][c].state == RED) {
        symbol = 'R';
      } else if (board[r][c].state == YELLOW) {
        symbol = 'Y';
      }

      mvwaddch(win, y, x, symbol);
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
