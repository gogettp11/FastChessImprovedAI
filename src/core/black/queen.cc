#include "../white/queen.h"
#include "../../board.h"
#include "../../common/config.h"
#include "../../common/util.h"
#include "../black_.h"
#include "../white/bishop.h"
#include "../white/king.h"
#include "../white/knight.h"
#include "../white/pawn.h"
#include "../white/rook.h"
#include "../white_.h"
#include "queen.h"

namespace black {

void Queen_Piece::pure_move(int i, int row_, int col_) {
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i] * UNIT;
  y[i] = row[i] * UNIT;
}

void Queen_Piece::pin(int k, std::string piece) {
  const std::vector<std::vector<int>> pinned_movelist = get_check_movelist(k);
  for (int i = 0; i < white::num_queens; i++) {
    if (piece == "Q" + std::to_string(i))
      filter(white::queen.movelist[i], pinned_movelist);
  }
  for (int i = 0; i < 2; i++) {
    if (piece == "B" + std::to_string(i))
      filter(white::bishop.movelist[i], pinned_movelist);
    else if (piece == "N" + std::to_string(i))
      filter(white::knight.movelist[i], pinned_movelist);
    else if (piece == "R" + std::to_string(i))
      filter(white::rook.movelist[i], pinned_movelist);
  }
  for (int i = 0; i < 8; i++) {
    if (piece == "P" + std::to_string(i))
      filter(white::pawn.movelist[i], pinned_movelist);
  }
}

void Queen_Piece::check_pin() {
  for (int i = 0; i < num_queens; i++) {
    if (alive[i]) {
      if (king_in_path(i) && num_pieces(i) == 1)
        pin(i, get_pinned_piece(i));
    }
  }
}

std::string Queen_Piece::get_pinned_piece(int i) {
  const std::vector<int> pos = {white::king.row, white::king.col};
  int row_;
  int col_;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] + 1;
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      row_++;
      col_++;
    }
  } else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] - 1;
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      row_++;
      col_--;
    }
  } else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] + 1;
    while (pos[0] < row_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      row_--;
      col_++;
    }
  } else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] - 1;
    while (pos[0] < row_) {
      if (white::blocks[row_][col_]) {
        return white::get_piece(row_, col_);
      }
      row_--;
      col_--;
    }
  } else if (pos[0] > row[i]) {
    row_ = row[i] + 1;
    col_ = col[i];
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      row_++;
    }
  } else if (pos[0] < row[i]) {
    row_ = row[i] - 1;
    col_ = col[i];
    while (pos[0] < row_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      row_--;
    }
  } else if (pos[1] > col[i]) {
    row_ = row[i];
    col_ = col[i] + 1;
    while (pos[1] > col_) {
      if (white::blocks[row_][col_])
        return white::get_piece(row_, col_);
      col_++;
    }
  } else if (pos[1] < col[i]) {
    row_ = row[i];
    col_ = col[i] - 1;
    while (pos[1] < col_) {
      if (white::blocks[row_][col_]) {
        return white::get_piece(row_, col_);
      }
      col_--;
    }
  }
}

int Queen_Piece::num_pieces(int i) {
  const std::vector<int> pos = {white::king.row, white::king.col};
  int row_;
  int col_;
  int total = 0;
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] + 1;
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_++;
      col_++;
    }
  } else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] - 1;
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_++;
      col_--;
    }
  } else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] - 1;
    while (pos[0] < row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_--;
      col_--;
    }
  } else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] + 1;
    while (pos[0] < row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_--;
      col_++;
    }
  }

  else if (pos[0] > row[i] && pos[1] == col[i]) {
    row_ = row[i] + 1;
    col_ = col[i];
    while (pos[0] > row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_++;
    }
  } else if (pos[0] < row[i] && pos[1] == col[i]) {
    row_ = row[i] - 1;
    col_ = col[i];
    while (pos[0] < row_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      row_--;
    }
  } else if (pos[1] > col[i] && pos[0] == row[i]) {
    row_ = row[i];
    col_ = col[i] + 1;
    while (pos[1] > col_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      col_++;
    }
  } else if (pos[1] < col[i] && pos[0] == row[i]) {
    row_ = row[i];
    col_ = col[i] - 1;
    while (pos[1] < col_) {
      if (white::blocks[row_][col_])
        total++;
      else if (blocks[row_][col_])
        return 0;
      col_--;
    }
  }
  return total;
}

bool Queen_Piece::king_in_path(int i) {
  const std::vector<int> pos = {white::king.row, white::king.col};
  int row_;
  int col_;
  row_ = row[i] + 1;
  col_ = col[i] + 1;
  while (row_ <= 7) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_++;
    col_++;
  }
  row_ = row[i] + 1;
  col_ = col[i] - 1;
  while (row_ <= 7) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_++;
    col_--;
  }
  row_ = row[i] - 1;
  col_ = col[i] - 1;
  while (row_ >= 0) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_--;
    col_--;
  }
  row_ = row[i] - 1;
  col_ = col[i] + 1;
  while (row_ >= 0) {
    if (row_ == pos[0] && col_ == pos[1])
      return true;
    row_--;
    col_++;
  }
  row_ = row[i] + 1;
  while (row_ <= 7) {
    if (row_ == pos[0] && col[i] == pos[1])
      return true;
    row_++;
  }
  row_ = row[i] - 1;
  while (row_ >= 0) {
    if (row_ == pos[0] && col[i] == pos[1])
      return true;
    row_--;
  }
  col_ = col[i] + 1;
  while (col_ <= 7) {
    if (col_ == pos[1] && row[i] == pos[0])
      return true;
    col_++;
  }
  col_ = col[i] - 1;
  while (col_ >= 0) {
    if (col_ == pos[1] && row[i] == pos[0])
      return true;
    col_--;
  }
  return false;
}

std::vector<std::vector<int>> Queen_Piece::get_check_movelist(int i) {
  std::vector<int> pos = {white::king.row, white::king.col};
  int row_;
  int col_;
  std::vector<std::vector<int>> ret;
  ret.push_back({row[i], col[i]});
  if (pos[0] > row[i] && pos[1] > col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] + 1;
    while (pos[0] > row_) {
      ret.push_back({row_, col_});
      row_++;
      col_++;
    }
  } else if (pos[0] > row[i] && pos[1] < col[i]) {
    row_ = row[i] + 1;
    col_ = col[i] - 1;
    while (pos[0] > row_) {
      ret.push_back({row_, col_});
      row_++;
      col_--;
    }
  } else if (pos[0] < row[i] && pos[1] > col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] + 1;
    while (pos[0] < row_) {
      ret.push_back({row_, col_});
      row_--;
      col_++;
    }
  } else if (pos[0] < row[i] && pos[1] < col[i]) {
    row_ = row[i] - 1;
    col_ = col[i] - 1;
    while (pos[0] < row_) {
      ret.push_back({row_, col_});
      row_--;
      col_--;
    }
  } else if (pos[0] > row[i]) {
    row_ = row[i] + 1;
    while (pos[0] > row_) {
      ret.push_back({row_, col[i]});
      row_++;
    }
  } else if (pos[0] < row[i]) {
    row_ = row[i] - 1;
    while (pos[0] < row_) {
      ret.push_back({row_, col[i]});
      row_--;
    }
  } else if (pos[1] > col[i]) {
    col_ = col[i] + 1;
    while (pos[1] > col_) {
      ret.push_back({row[i], col_});
      col_++;
    }
  } else if (pos[1] < col[i]) {
    col_ = col[i] - 1;
    while (pos[1] < col_) {
      ret.push_back({row[i], col_});
      col_--;
    }
  }
  return ret;
}

std::vector<int> Queen_Piece::get_avoid_move(int i) {
  const std::vector<int> pos = {white::king.row, white::king.col};
  std::vector<int> ret;
  if (pos[0] > row[i] && pos[1] > col[i])
    ret = {pos[0] + 1, pos[1] + 1};
  else if (pos[0] < row[i] && pos[1] > col[i])
    ret = {pos[0] - 1, pos[1] + 1};
  else if (pos[0] > row[i] && pos[1] < col[i])
    ret = {pos[0] + 1, pos[1] - 1};
  else if (pos[0] < row[i] && pos[1] < col[i])
    ret = {pos[0] - 1, pos[1] - 1};
  else if (pos[0] > row[i])
    ret = {pos[0] + 1, pos[1]};
  else if (pos[0] < row[i])
    ret = {pos[0] - 1, pos[1]};
  else if (pos[1] > col[i])
    ret = {pos[0], pos[1] + 1};
  else if (pos[1] < col[i])
    ret = {pos[0], pos[1] - 1};
  return ret;
}

void Queen_Piece::update_movelist() {
  for (int i = 0; i < num_queens; i++) {
    if (!alive[i])
      continue;
    movelist[i].clear();
    protecting_movelist[i].clear();
    int row_ = row[i] + 1;
    int col_ = col[i] + 1;
    while (row_ <= 7 && col_ <= 7) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_++;
      col_++;
    }
    row_ = row[i] - 1;
    col_ = col[i] + 1;
    while (row_ >= 0 && col_ <= 7) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_--;
      col_++;
    }
    row_ = row[i] + 1;
    col_ = col[i] - 1;
    while (row_ <= 7 && col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_++;
      col_--;
    }
    row_ = row[i] - 1;
    col_ = col[i] - 1;
    while (row_ >= 0 && col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_--;
      col_--;
    }
    row_ = row[i] - 1;
    col_ = col[i];
    while (row_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_--;
    }
    row_ = row[i] + 1;
    col_ = col[i];
    while (row_ < 8) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      row_++;
    }
    row_ = row[i];
    col_ = col[i] + 1;
    while (col_ < 8) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      col_++;
    }
    row_ = row[i];
    col_ = col[i] - 1;
    while (col_ >= 0) {
      if (blocks[row_][col_]) {
        protecting_movelist[i].push_back({row_, col_});
        break;
      }
      movelist[i].push_back({row_, col_});
      if (white::blocks[row_][col_])
        break;
      col_--;
    }
  }
}

void Queen_Piece::move(int i, int row_, int col_) {
  blocks[row[i]][col[i]] = 0;
  blocks[row_][col_] = 1;
  row[i] = row_;
  col[i] = col_;
  x[i] = col[i] * UNIT;
  y[i] = row[i] * UNIT;
}

void Queen_Piece::show() {
  for (int i = 0; i < num_queens; i++) {
    if (!alive[i])
      continue;
    if (!texture.loadFromFile("assets/sprites/blackqueen.png"))
      return;
    sprite.setTexture(texture);
    sprite.setScale(board.pieces_scale, board.pieces_scale);
    sprite.setPosition(x[i] + board.pieces_paddingx,
                       y[i] + board.pieces_paddingy);
    window.draw(sprite);
  }
}

} // namespace black
