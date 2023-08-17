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
    black::show();
    white::show();
    white::show_legal_moves();
    board.check_end();
    window.display();
    black::ai::gen_move();
    window.display();
  }
  return 0;
}
