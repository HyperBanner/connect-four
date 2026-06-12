#include "../include/board.h"
#include <stdlib.h>

cell_t (*init_board(void))[7] {
  int rows = 6;
  int cols = 7;

  cell_t(*board)[cols] = malloc(rows * sizeof(*board));
  if (board == NULL)
    return NULL;

  for (int r = 1; r <= rows; ++r) {
    for (int c = 1; c <= cols; ++c) {
      board[r][c].state = EMPTY;
      board[r][c].row_num = r;
      board[r][c].col_num = c;
    }
  }

  return board;
}
