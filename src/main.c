#include "../include/board.h"
#include "../include/ui.h"
#include <ncurses.h>
#include <panel.h>

void draw(WINDOW *win, cell_t board[6][7]) {
  werase(win);
  draw_ui(win);
  draw_board(win, board);
  wrefresh(win);
}

int main(int argc, char **argv) {
  // Init functions
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();

  int screen_rows, screen_cols;
  getmaxyx(stdscr, screen_rows, screen_cols);

  int height = 6 * 3;
  int width = 7 * 3 * 2;

  int starty = (screen_rows - height) / 2;
  int startx = (screen_cols - width) / 2;

  if (starty < 0)
    starty = 0;
  if (startx < 0)
    startx = 0;

  WINDOW *board_win = newwin(height, width, starty, startx);

  if (board_win == NULL) {
    endwin();
    printf("newwin failed\n");
    return 1;
  }

  cell_t(*board)[7] = init_board();

  // Keep program alive until 'q' is pressed
  while (1) {
    draw(board_win, board);

    int ch = getch();
    if (ch == 'q')
      break;

    // handle moves
  }

  delwin(board_win);
  endwin();
  return 0;
}
