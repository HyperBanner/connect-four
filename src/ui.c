#include "../include/board.h"
#include <ncurses.h>
#include <string.h>

#define CELL_H 3
#define CELL_W 6

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

void draw_board(WINDOW *win, cell_t board[6][7]) {
  // draw
  box(win, 0, 0);

  for (int r = 0; r < 6; ++r) {
    for (int c = 0; c < 7; ++c) {

      int y = 1 + r * CELL_H;
      int x = 2 + c * CELL_W;

      char symbol = '0';

      if (board[r][c].state == RED) {
        wattron(win, COLOR_PAIR(1));
        symbol = 'R';
      } else if (board[r][c].state == YELLOW) {
        wattron(win, COLOR_PAIR(2));
        symbol = 'Y';
      }

      mvwaddch(win, y, x, symbol);
      wattroff(win, COLOR_PAIR(1));
      wattroff(win, COLOR_PAIR(2));
    }
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

    // Upper indication
    mvwprintw(win, 1, 6, "Who will go first?");

    // arrows
    if (selected == 0) {
      mvwprintw(win, 2, 6, "v");
    } else {
      mvwprintw(win, 2, 20, "v");
    }

    // Red Player
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 3, 2, "Red Player");
    wattroff(win, COLOR_PAIR(1));

    // Yellow Player
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 15, "Yellow Player");
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
      delwin(win);
      return selected == 0 ? RED : YELLOW;
    }
  }
}
