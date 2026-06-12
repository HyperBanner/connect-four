#pragma once

typedef enum State { EMPTY, RED, YELLOW } state_t;

typedef struct Cell {
  int row_num;
  int col_num;
  state_t state;
} cell_t;

cell_t (*init_board(void))[7];
