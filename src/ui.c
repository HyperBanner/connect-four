#include "../include/board.h"
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

void draw_turn_indicator(int starty, state_t current_player) {
  move(starty - 2, 0);
  clrtoeol();

  int x = (COLS - 20) / 2;
  mvprintw(starty - 2, x, "Turn: ");

  if (current_player == RED) {
    attron(COLOR_PAIR(1));
    printw("Red Player");
    attroff(COLOR_PAIR(1));
  } else {
    attron(COLOR_PAIR(2));
    printw("Yellow Player");
    attroff(COLOR_PAIR(2));
  }
}

// pre-game selection menu
state_t choose_player(void) {
  int selected = 0;

  int height = 5;
  int width = 30;

  int y = (LINES - height) / 2;
  int x = (COLS - width) / 2;

  WINDOW *win = newwin(height, width, y, x);

  while (1) {
    werase(win);
    box(win, 0, 0);

    // arrows
    if (selected == 0) {
      mvwprintw(win, 1, 6, "v");
    } else {
      mvwprintw(win, 1, 20, "v");
    }

    // Red Player
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 2, 2, "Red Player");
    wattroff(win, COLOR_PAIR(1));

    // Yellow Player
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 2, 15, "Yellow Player");
    wattroff(win, COLOR_PAIR(2));

    wrefresh(win);

    int ch = getch();

    switch (ch) {
    case KEY_LEFT:
      selected = 0;
      break;

    case KEY_RIGHT:
      selected = 1;
      break;

    case ' ':
    case '\n':
      delwin(win);
      return selected == 0 ? RED : YELLOW;
    }
  }
}
