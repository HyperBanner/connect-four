#include "../include/board.h"
#include <ncurses.h>

void draw_selection(WINDOW *win, int selected_col);
void draw_controls(int starty, int board_height);
void draw_turn_indicator(int starty, state_t current_player);
state_t choose_player(void);
