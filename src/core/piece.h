#ifndef CORE_PIECE_H
#define CORE_PIECE_H

#include "../common/config.h"
#include <SFML/Graphics.hpp>
#include <vector>

// The abstract interface for all piece classes.
class Piece {
public:
  sf::Sprite sprite;
  sf::Texture texture;
  std::vector<int> row, col, y, x;
  std::vector<std::vector<std::vector<int>>> movelist, protecting_movelist,
      hit_movelist;
  std::vector<bool> alive;

protected:
  virtual void update_movelist() = 0;
  virtual void show() = 0;
};

#endif // CORE_PIECE_H
