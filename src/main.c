#include "../include/board.h"
#include <ncurses.h>
#include <panel.h>

int main(int argc, char **argv) {

  initscr();
  printw("Press any key");
  refresh();

  char letter = getch();
  clear();
  printw("You pushed: '%c'", letter);
  refresh();

  getch();
  endwin();

  return 0;
}
