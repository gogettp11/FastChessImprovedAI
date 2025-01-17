#include "../black/pawn.h"
#include "../../board.h"
#include "../../common/config.h"
#include "../black/bishop.h"
#include "../black/king.h"
#include "../black/knight.h"
#include "../black/queen.h"
#include "../black/rook.h"
#include "../black_.h"
#include "../white_.h"
#include "pawn.h"

namespace white {

void Pawn_Piece::pure_move(int i, int row_, int col_) {
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i] * UNIT;
  y[i] = row[i] * UNIT;
}

void Pawn_Piece::update_movelist() {
  for (int i = 0; i < 8; i++) {
    if (!alive[i])
      continue;
    movelist[i].clear();
    hit_movelist[i].clear();
    if (row[i] > 0 && black::blocks[row[i] - 1][col[i]] == 0 &&
        blocks[row[i] - 1][col[i]] == 0) {
      movelist[i].push_back({row[i] - 1, col[i]});
      if (row[i] == 6 && black::blocks[row[i] - 2][col[i]] == 0 &&
          blocks[row[i] - 2][col[i]] == 0)
        movelist[i].push_back({row[i] - 2, col[i]});
    }
    if (row[i] > 0 && col[i] > 0) {
      if (black::blocks[row[i] - 1][col[i] - 1] == 1 &&
          blocks[row[i] - 1][col[i] - 1] == 0)
        movelist[i].push_back({row[i] - 1, col[i] - 1});
      hit_movelist[i].push_back({row[i] - 1, col[i] - 1});
    }
    if (row[i] > 0 && col[i] < 7) {
      if (black::blocks[row[i] - 1][col[i] + 1] == 1 &&
          blocks[row[i] - 1][col[i] + 1] == 0)
        movelist[i].push_back({row[i] - 1, col[i] + 1});
      hit_movelist[i].push_back({row[i] - 1, col[i] + 1});
    }
    if (row[i] == 3) {
      for (int k = 0; k < 8; k++) {
        if (black::en_passant[k] && !blocks[2][black::pawn.col[k]]) {
          if (abs(col[i] - black::pawn.col[k]) == 1)
            movelist[i].push_back({2, black::pawn.col[k]});
        }
      }
    }
  }
}

void Pawn_Piece::move(int i, int row_, int col_) {
  if (abs(row_ - row[i]) == 2)
    en_passant[i] = 1;
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i] * UNIT;
  y[i] = row[i] * UNIT;
}

void Pawn_Piece::print_movelist() {
  for (int i = 0; i < 8; i++) {
    printf("P%d: ", i);
    for (int k = 0; k < movelist[i].size(); k++) {
      for (int j = 0; j < movelist[i][k].size(); j++)
        printf("%d ", movelist[i][k][j]);
      printf("  ");
    }
    printf("\n");
  }
  printf("\n");
}

void Pawn_Piece::show() {
  for (int i = 0; i < 8; i++) {
    if (!alive[i])
      continue;
    if (!texture.loadFromFile("assets/sprites/whitepawn.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(board.pieces_scale, board.pieces_scale);
    sprite.setPosition(x[i] + board.pieces_paddingx,
                       y[i] + board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace white
