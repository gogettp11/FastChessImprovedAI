#include "board.h"
#include "common/config.h"
#include "common/util.h"
#include "core/black_.h"
#include "core/white_.h"
#include "player/event_processor.h"
#include "queue.h"

#ifdef IS_BLACK_AI
#include "ai/black/search.h"
#endif

#define WINDOW_X_POS 950
#define WINDOW_Y_POS 180

int main() {
  srand(time(NULL));
  black::init();
  white::init();
  Event_Processor processor;
  init(GAME_ENV);
  board.update_moves();
  window.setPosition(sf::Vector2i(WINDOW_X_POS, WINDOW_Y_POS));
  while (window.isOpen()) {
    processor.handleEvents();
    window.clear();
    board.draw_board();
    board.select(board.selected_row, board.selected_col);
    black::show();
    white::show();
    if (white::turn && board.clicked_coords[0] != -1 &&
        board.clicked_coords[1] != -1)
      if (white::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
        white::show_legal_moves();
#if !defined(IS_BLACK_AI)
    if (black::turn && board.clicked_coords[0] != -1 &&
        board.clicked_coords[1] != -1)
      if (black::blocks[board.clicked_coords[0]][board.clicked_coords[1]])
        black::show_legal_moves();
#endif
    board.check_end();
    window.display();
#ifdef SCREENSHOTS_ON
    white::check_capture_screen();
    black::check_capture_screen();
#endif
#ifdef IS_BLACK_AI
    if (black::turn && !board.checkmate && !board.stalemate)
      black::ai::gen_move();
#endif
    window.display();
  }
  return 0;
}
