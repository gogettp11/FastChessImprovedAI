#ifndef CORE_WHITE__H
#define CORE_WHITE__H

#include <string>

namespace white {
extern std::vector<std::vector<int>> blocks;
extern int num_queens;
extern std::vector<std::string> checker;
extern std::vector<bool> en_passant;
extern bool turn;
extern bool screenshot;
extern std::string last_clicked_piece;

std::map<std::string, std::vector<std::vector<int>>> get_moves();
void check_capture_screen();
void handle_undo_promotion(int i, int row, int col);
void revive(std::string piece, int row, int col);
void reset_enpassant();
void valid_move(bool is_undo, bool killed, std::string piece, int row, int col);
void castle_K(bool is_undo);
void castle_Q(bool is_undo);
void kill(bool is_undo, std::string piece, int row, int col);
void move_piece(std::string piece, int row, int col);
void move_piece(std::string piece, int row, int col);
std::string get_piece(int row_, int col_);
void play();
void print_blocks();
#ifdef DEBUGAI
void print_blocks_log();
#endif
void show();
void init();
void show_legal_moves();
void drag_and_drop();
void reset_sprite_pos();

} // namespace white

#endif // CORE_WHITE__H
