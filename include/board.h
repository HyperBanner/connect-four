#pragma once

#include <ncurses.h>

typedef enum State { EMPTY, RED, YELLOW } state_t;

typedef struct Cell {
  int row_num;
  int col_num;
  state_t state;
} cell_t;

cell_t (*init_board(void))[7];
void draw_board(WINDOW *win, cell_t board[6][7]);
void draw_cell(WINDOW *win, int row, int col, char piece);
void drop_chip(cell_t board[6][7], int selected_col, state_t color);
