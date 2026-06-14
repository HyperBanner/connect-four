#include "../include/board.h"
#include <ncurses.h>

void draw_selection(WINDOW *win, int selected_col);

void draw_controls(int starty, int board_height);

void draw_turn_indicator(int starty, state_t current_player);

void draw_board(WINDOW *win, cell_t board[6][7]);

state_t choose_player(void);
