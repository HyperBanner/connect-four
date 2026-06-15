#pragma once

#include "../include/board.h"
#include <ncurses.h>

void draw_selection(WINDOW *win, int selected_col);

void draw_controls(int starty, int board_height);

void draw_turn_indicator(int starty, state_t current_player, bool game_over,
                         bool draw_game);

void draw_board(WINDOW *win, cell_t board[6][7]);

void draw(WINDOW *board_win, WINDOW *selection_win, cell_t board[6][7],
          int starty, int board_height, int selected_col,
          state_t current_player, bool game_over, bool draw_game);

state_t choose_player(void);
