#include "../../../include/common.h"

namespace Black {

void Pawn_Piece::update_movelist() {
  for (int i=0;i<8;i++) {
    movelist[i].clear();
    if (row[i] < 8 && White::blocks[row[i]+1][col[i]] == 0 && blocks[row[i]+1][col[i]] == 0) {
      movelist[i].push_back({row[i]+1, col[i]});
      if (row[i] == 1)
        movelist[i].push_back({row[i]+2, col[i]});
    }
    if (row[i] < 7 && col[i] < 7) {
      if (White::blocks[row[i]+1][col[i]+1] == 1)
        movelist[i].push_back({row[i]+1, col[i]+1});
    }
    if (row[i] < 7 && col[i] > 0) {
      if (White::blocks[row[i]+1][col[i]-1] == 1)
        movelist[i].push_back({row[i]+1, col[i]-1});
    }
  }
}

void Pawn_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i]*UNIT;
  y[i] = row[i]*UNIT;
}

void Pawn_Piece::show() {
  for (int i=0;i<8;i++) {
    if (!alive[i])
      continue;
    sf::Texture texture;
    if (!texture.loadFromFile("assets/sprites/blackPawn.png"))
      return;
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(Board.pieces_scale, Board.pieces_scale);
    sprite.setPosition(x[i] + Board.pieces_paddingx, y[i] + Board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace Black
