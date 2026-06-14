#include "../include/board.h"
#include <ncurses.h>
#include <stdlib.h>

cell_t (*init_board(void))[7] {
  cell_t(*board)[7] = malloc(6 * sizeof(*board));
  if (board == NULL) {
    return NULL;
  }

  for (int row = 0; row < 6; ++row) {
    for (int col = 0; col < 7; ++col) {
      board[row][col].state = EMPTY;
    }
  }

  return board;
}

int drop_chip(cell_t board[6][7], int selected_col, state_t player) {
  for (int row = 5; row >= 0; --row) {
    if (board[row][selected_col].state == EMPTY) {
      board[row][selected_col].state = player;
      return row;
    }
  }
  return -1; // column full
}

// helper for check_winner
int count_direction(cell_t board[6][7], int row, int col, int dr, int dc,
                    state_t player) {
  int count = 0;

  row += dr;
  col += dc;

  while (row >= 0 && row < 6 && col >= 0 && col < 7 &&
         board[row][col].state == player) {
    count++;

    row += dr;
    col += dc;
  }

  return count;
}

bool check_winner(cell_t board[6][7], int row, int col, state_t player) {
  const int directions[4][2] = {
      {0, 1}, // horizontal
      {1, 0}, // vertical
      {1, 1}, // diagonal
      {-1, 1} // other diagonal
  };

  for (int d = 0; d < 4; ++d) {
    int dr = directions[d][0];
    int dc = directions[d][1];

    int total = 1; // newly placed chip

    // check all directions
    total += count_direction(board, row, col, dr, dc, player);
    total += count_direction(board, row, col, -dr, -dc, player);

    if (total >= 4) {
      return true;
    }
  }
  return false;
}

bool board_full(cell_t board[6][7]) {
  for (int row = 0; row < 6; ++row) {
    for (int col = 0; col < 7; ++col) {
      if (board[row][col].state == EMPTY) {
        return false;
      }
    }
  }
  return true;
}
