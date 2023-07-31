#include "../white/eval.h"
#include "../../board.h"
#include "../../common/config.h"
#include "../../core/black/bishop.h"
#include "../../core/black/king.h"
#include "../../core/black/knight.h"
#include "../../core/black/pawn.h"
#include "../../core/black/queen.h"
#include "../../core/black/rook.h"
#include "../../core/black_.h"
#include "../../core/white/bishop.h"
#include "../../core/white/king.h"
#include "../../core/white/knight.h"
#include "../../core/white/pawn.h"
#include "../../core/white/queen.h"
#include "../../core/white/rook.h"
#include "../../core/white_.h"
#include "../../media/text.h"
#include "../../queue.h"
#include "../helper.h"
#include "eval.h"
#include "search.h"

namespace black {
namespace eval {

// General mobility: the number of open positions available to non-BRQ each
// piece.
double mobility() {
  double reward = 0;
  for (int i = 0; i < 2; i++) {
    if (knight.alive[i]) {
      for (int k = 0; k < knight.movelist[i].size(); k++)
        reward += MOBILITY;
    }
    if (bishop.alive[i]) {
      for (int k = 0; k < bishop.movelist[i].size(); k++)
        reward += MOBILITY;
    }
    if (rook.alive[i]) {
      for (int k = 0; k < rook.movelist[i].size(); k++)
        reward += MOBILITY;
    }
  }
  for (int i = 0; i < num_queens; i++) {
    for (int k = 0; k < queen.movelist[i].size(); k++)
      reward += MOBILITY;
  }
  return reward;
}

double pawn_promote() {
  double reward = 0;
  for (int i = 0; i < 8; i++) {
    if (pawn.row[i] >= 7)
      reward += PROMOTION_REWARD;
  }
  return reward;
}

double bishop_pair() {
  double reward = 0;
  if (bishop.alive[0] && bishop.alive[1])
    reward += BISHOP_PAIR_REWARD;
  return reward;
}
} // namespace eval
} // namespace black
