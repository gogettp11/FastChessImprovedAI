#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <tuple>
#include <vector>

using colours = std::tuple<int, int, int>;

class Game_Board {
  // TODO: if needed create file with custom data types and move it to file
  colours brown = std::make_tuple(92, 48, 17);
  colours white = std::make_tuple(180, 180, 180);
  colours light_brown = std::make_tuple(173, 199, 137);

public:
  int total_moves;
  int pieces_paddingx, pieces_paddingy;
  float pieces_scale;
  bool checkmate, stalemate;
  bool isFrozen;
  int screenshot_num;
  std::string clicked_piece;
  int selected_row, selected_col;
  std::pair<int, int> clicked_coords;
  Game_Board() {
    clicked_coords = {-1, -1};
    clicked_piece = "";
    screenshot_num = 1;
    selected_row = selected_col = -1;
    checkmate = false;
    stalemate = false;
    total_moves = 0;
    pieces_paddingx = 13;
    pieces_paddingy = 8;
    pieces_scale = 1;
    isFrozen = false;
  };
  void Circle(int row, int col);
  void reset_pos();
  void print_undo();
  void check_end();
  void pop();
  void update_moves();
  void play();
  void draw_board();
  std::vector<int> get_coords(int x, int y);
  void select(int row, int col);

private:
  void drawRect(colours &color, int x, int y, int width, int height);
};

extern Game_Board board;

#endif // BOARD_H
