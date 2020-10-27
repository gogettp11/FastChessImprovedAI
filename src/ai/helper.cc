#include "../common.h"

namespace Black { namespace AI {
std::map<std::string, std::vector<std::vector<int>>>
shuffle(std::map<std::string, std::vector<std::vector<int>>>) {

}

int evaluate_pos() {
  int score = 0;
  if (Black::King.alive)
    score -= 3;
  for (int i=0;i<Black::num_queens;i++) {
    if (Black::Queen.alive[i])
      score -= 9;
  }
  for (int i=0;i<8;i++) {
    if (Black::Pawn.alive[i])
      score -= 1;
  }
  for (int i=0;i<2;i++) {
    if (Black::Bishop.alive[i])
      score -= 3;
    if (Black::Knight.alive[i])
      score -= 3;
    if (Black::Rook.alive[i])
      score -= 5;
  }
  if (White::King.alive)
    score += 3;
  for (int i=0;i<White::num_queens;i++) {
    if (White::Queen.alive[i])
      score += 9;
  }
  for (int i=0;i<8;i++) {
    if (White::Pawn.alive[i])
      score += 1;
  }
  for (int i=0;i<2;i++) {
    if (White::Bishop.alive[i])
      score += 3;
    if (White::Knight.alive[i])
      score += 3;
    if (White::Rook.alive[i])
      score += 5;
  }
  return score;
}

std::map<std::string, std::vector<std::vector<int>>> get_white_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (White::King.alive && !White::King.movelist.empty())
    moves["K"] = White::King.movelist;
  for (int i=0;i<White::num_queens;i++) {
    if (White::Queen.alive[i] && !White::Queen.movelist[i].empty())
      moves["Q" + str(i)] = White::Queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (White::Pawn.alive[i] && !White::Pawn.movelist[i].empty())
      moves["P" + str(i)] = White::Pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (White::Bishop.alive[i] && !White::Bishop.movelist[i].empty())
      moves["B" + str(i)] = White::Bishop.movelist[i];
    if (White::Knight.alive[i] && !White::Knight.movelist[i].empty())
      moves["N" + str(i)] = White::Knight.movelist[i];
    if (White::Rook.alive[i] && !White::Rook.movelist[i].empty())
      moves["R" + str(i)] = White::Rook.movelist[i];
  }
  return moves;
}

std::map<std::string, std::vector<std::vector<int>>> get_black_moves() {
  std::map<std::string, std::vector<std::vector<int>>> moves = {};
  if (Black::King.alive && !Black::King.movelist.empty())
    moves["K"] = Black::King.movelist;
  for (int i=0;i<Black::num_queens;i++) {
    if (Black::Queen.alive[i] && !Black::Queen.movelist[i].empty())
      moves["Q" + str(i)] = Black::Queen.movelist[i];
  }
  for (int i=0;i<8;i++) {
    if (Black::Pawn.alive[i] && !Black::Pawn.movelist[i].empty())
      moves["P" + str(i)] = Black::Pawn.movelist[i];
  }
  for (int i=0;i<2;i++) {
    if (Black::Bishop.alive[i] && !Black::Bishop.movelist[i].empty())
      moves["B" + str(i)] = Black::Bishop.movelist[i];
    if (Black::Knight.alive[i] && !Black::Knight.movelist[i].empty())
      moves["N" + str(i)] = Black::Knight.movelist[i];
    if (Black::Rook.alive[i] && !Black::Rook.movelist[i].empty())
      moves["R" + str(i)] = Black::Rook.movelist[i];
  }
  return moves;
}

} // namespace AI
} // namespace Black