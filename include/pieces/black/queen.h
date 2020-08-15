#ifndef BLACK_QUEEN_H
#define BLACK_QUEEN_H

namespace Black {

class Queen_Piece : public Piece {
private:
public:
  std::vector<std::vector<int>> movelist;
  int row, col, y, x;
  bool alive;
  Queen_Piece() {
    alive = true;
    row = 0;
    col = 4;
    y = row*UNIT;
    x = col*UNIT;
  };
  void move(int row_, int col_);
  void update_movelist();
  void show();
};

} // namespace Black

#endif // BLACK_QUEEN_H
