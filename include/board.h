#pragma once

#include <ncurses.h>

typedef enum State { EMPTY, RED, YELLOW } state_t;

typedef struct Cell {
  state_t state;
} cell_t;

cell_t (*init_board(void))[7];

void animate_chip(WINDOW *win, cell_t board[6][7], int selected_col,
                  state_t color);

int drop_chip(cell_t board[6][7], int selected_col, state_t player,
              WINDOW *board_win, WINDOW *selection_win, int starty, int height,
              bool game_over, bool draw_game);

int count_direction(cell_t board[6][7], int row, int col, int dr, int dc,
                    state_t player);

bool check_winner(cell_t board[6][7], int row, int col, state_t player);

bool board_full(cell_t board[6][7]);
