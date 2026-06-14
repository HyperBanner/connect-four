#include <ncurses.h>
#include <string.h>

void draw_selection(WINDOW *win, int selected_col) {
  int x = 2 + selected_col * 6;
  mvwaddch(win, 1, x, 'v');
}

void draw_controls(int starty, int board_height) {
  char *msg = "Arrows: Switch columns | Space: Drop Chip | q: Quit";
  mvprintw(starty + board_height + 3, (COLS - strlen(msg)) / 2, "%s", msg);
}
